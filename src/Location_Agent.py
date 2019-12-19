import pickle as pkl
import numpy as np
import torch
import torch.nn as nn
import icp
import random
import matplotlib.pyplot as plt

#def pi
pi = 4 * np.arctan(1)

def init():
    #importing maps as initialization
    #importing demo Radar result as Map 'Gene'
    with open('map.pkl', 'rb') as file:
        m = np.asarray(pkl.load(file))
    with open('demo.pkl', 'rb') as file2:
        Gene = pkl.load(file2)
        
    height = m.shape[0]
    width = m.shape[1]

    print(height, width)

    #get and plot the margin of the rooms(walls, AKA)
    x = np.zeros(1000000)
    y = np.zeros(1000000)

    Sum_Margin = 0

    for i in range(1000):
        for j in range(1000):
            if m[i][j] == 0:
                x[Sum_Margin] = i; y[Sum_Margin] = j
                Sum_Margin+=1
    plt.scatter(x, y, s = 0.01)
    plt.show()
    
    return x[:Sum_Margin], y[:Sum_Margin], Gene

#two util functions
def Calc_Arg(vec):
    w = np.sqrt(vec[0] * vec[0] + vec[1] * vec[1])
    cosine = vec[0] / w
    sine = vec[1] / w
    comp = cosine + sine * 1j
    return np.log(comp).imag

def Rev_Calc_Arg(arg, radius):
    mx = radius * np.cos(arg)
    my = radius * np.sin(arg)
    return mx, my

#an agent to determine where the TURTLEBOT 2 is...
class Agent():
    delt_arg = pi / 360
    Max_Argument = 720
    #Argument = 0
    
    Approx_Loc = np.zeros(2)
    Loc = np.zeros(2, dtype = float)
    Real_Radar = {}
    Fake_Radar = {}
    tmptest = {}
    message = {}
    
    hindrance = {}
    
    #netReg = Net()
    
    def __init__(self, r, loc = [400, 400], argument = 0, max_argument = 720):
        self.Max_Argument = max_argument
        self.Argument = argument
        #plz input r as a list or a numpy array of max_argument elements
        for i in range(max_argument):
            self.Real_Radar[(i + argument) % max_argument] = r[i]
        self.Approx_Loc = np.asarray(loc)
        self.Loc = np.asarray(loc, dtype = float)
        #print(self.Approx_Loc)
        return
    
    #Generate Fake Radar distances
    def fake(self, x, y):
        argu_well = {}
        argument = 0
        for i in range(x.shape[0]):
            p = np.array([x[i] - self.Approx_Loc[0], y[i] - self.Approx_Loc[1]])
            #print(x[i], y[i], p)
            tmp_d = np.sqrt(p[0] * p[0] +  p[1] * p[1])
            tmp_a = (int(Calc_Arg(p) / self.delt_arg + 0.5)) % self.Max_Argument
            #print("miao", tmp_a, tmp_d)
            #print(argu_well.keys())
            if tmp_a in argu_well.keys() and tmp_d >= argu_well[tmp_a]:
                continue
            argu_well[tmp_a] = tmp_d
            #i = i - argument
        self.Fake_Radar = argu_well
        #self.arg2ind()
        return
    Real_P = np.zeros((Max_Argument, 2))
    Fake_P = np.zeros((Max_Argument, 2))
    
    #from polar_indices(distances) to Dicarle_indices
    def arg2ind(self):
        for key in self.Fake_Radar.keys():
            value = self.Fake_Radar[key]
            vvalue = self.Real_Radar[key]
            #print(key * self.delt_arg, vvalue)
            self.Real_P[key][0], self.Real_P[key][1] = Rev_Calc_Arg(key * self.delt_arg, vvalue)
            self.Fake_P[key][0], self.Fake_P[key][1] = Rev_Calc_Arg(key * self.delt_arg, value)
    
    #use the method of ICP Point Cloud Matching to match the two Point Clouds
    def move_to_right(self):
        T, dist, _ = icp.icp(self.Real_P, self.Fake_P, max_iterations= 20)
        #assert dist < 1e-2  
        self.Loc[0] += T[0][2]
        self.Loc[1] += T[1][2]
        #print(T[0][0], T[1][0], self.Loc)
        self.Argument = Calc_Arg([T[0][0], T[1][0]]) / self.delt_arg % self.Max_Argument + 0.5
        print("The Precise Location of the Agent is (%.0f, %.0f) with Argument %d" % (self.Loc[0], self.Loc[1], self.Argument))
        
        self.Loc[0] -= T[0][2]
        self.Loc[1] -= T[1][2]
               
        start = []
        end = []
        flag = False
        for i in range(dist.shape[0]):
            if dist[i] > 40:
                #if i == self.Max_Argument - 1: break
                self.hindrance[i] = self.Real_Radar[i]
                if flag == False:
                    print(i)
                    start.append(i)
                    flag = True
            if dist[i] <= 40 and flag:
                end.append(i)
                flag = False
                #i+=1
        
        start = np.array(start)
        end = np.array(end)
        for i in range(start.shape[0]):
            print("Possible human tracks on with Argument Range %d to %d" % (start[i], end[i]))
            
        #second_time_optimization with hindrance available
        for i in range(start.shape[0]):
            st = self.Real_Radar[start[i] - 1]; ed = self.Real_Radar[end[i]];
            inv = end[i] - start[i] + 1
            for j in range(start[i], end[i]):
                self.Real_Radar[j] = st + (ed - st) * (j - start[i] + 1) / inv
                print(self.Real_Radar[j - 1])
                
        self.arg2ind()
        T, dist, _ = icp.icp(self.Real_P, self.Fake_P, max_iterations= 40)
        #assert dist < 1e-2
        self.Loc[0] += T[0][2]
        self.Loc[1] += T[1][2]
        #print(T[0][0], T[1][0], self.Loc)
        self.Argument = Calc_Arg([T[0][0], T[1][0]]) / self.delt_arg % self.Max_Argument + 0.5
        print("The Precise Location of the Agent is (%.0f, %.0f) with Argument %d" % (self.Loc[0], self.Loc[1], self.Argument))
    def show_warning(self):
        self.WarX = []
        self.WarY = []
        for i in self.hindrance.keys():
            mx, my = Rev_Calc_Arg ((i + self.Argument) * self.delt_arg % self.Max_Argument, 50) #self.hindrance[i])
            self.WarX.append(mx)
            self.WarY.append(my)
        
        plt.title('Warning: Possible Human Tracks')
        plt.scatter(self.WarX, self.WarY, s = 0.2)
        plt.scatter(0,0, color = 'r', s = 0.5)
        plt.show()

#a sample for using this agent
#"location" argument is the predicted argument by another sub-group, is an approximation of the final location
def Call_Agent(x, y, r, arg = 0, location = [430, 430], interval = 0):
    agent = Agent(r, argument = arg, loc = location)
    
    agent.fake(x, y)
    agent.arg2ind()
    agent.move_to_right()
    
    #print(agent.optimize())
    
    agent.show_warning()
    
    #print 2 point clouds discussed before
    plt.scatter([agent.Real_P[i][0] for i in range(agent.Real_P.shape[0])],
                [agent.Real_P[i][1] for i in range(agent.Real_P.shape[0])], s = 0.01, color = 'g')
    plt.scatter([agent.Fake_P[i][0] for i in range(agent.Fake_P.shape[0])],
                [agent.Fake_P[i][1] for i in range(agent.Fake_P.shape[0])], s = 0.01, color = 'b')
    
    plt.show()
    
    
    
    return  {"position": agent.Loc, "Argument": agent.Argument, "hindrance": agent.hindrance, "interval": interval + 1}
    

def main():
    x, y, Gene = init()
    
    #Gene is some  demo data of Radar Input, in Numpy Array of size Max_Argument,
    #which indicates how many distances can be generated by the radar.
    msg = Call_Agent(x, y, Gene)


if __name__ == '__main__':
    main()



