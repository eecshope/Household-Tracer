# Household-Turtlebot-2
## Environment Description

The world is a grid-like world, formed by several squares. For example, think of the famous game: the battle of tanks.

  To simplify the environment, we assume that the human and the robot can move and stay from grid to grid while standing on two grids is forbidden. In other words,  the human and the robot can be seen either a mass point or a unit square. 

Beside paths and walls, some blocks are also needed, and with no doubt the blocks should be squares. which cannot stand across grids as well. By doing this, we can pay minimum effort in the block-detection algorithm.

**Attention! The map should be the robot's inherent knowledge rather than learning from scratch.**

## CV Group

The CV Group should use the optimal signals to locate the person and itself. At the beginning of a time interval, the CV component should give the person's current location to the MV Group instantly. At the same time, an accurate position of the center should be reported using the last-time position from the MV group and the optimal signals as info.

If the human body is found on multiple grids, just return the mass center's location.

Besides, the CV Group should report the blocks and walls in the movable area at the same time. 

## MV Group

 At the beginning of each time interval, the MV Group should request the CV Group for the human's location and the surrounding blocks. 

If the human is in sight, just choose the right direction and go straight at him.

If it lose contact with the human, the robot should speed up to search the human. **The turtle has a limited capacity of memory, which can store the position, the velocity(as a vector) of both the robot and the human(if observed) at the beginning and the end of several previous time intervals**. So the robot should refer to the history and make a decision, thinking combined with the policy.

At the end of the interval, the robot should report its position and velocity to the CV Group.

The position and velocity of the robot (not the human) is determined by the gyroscope and the optimal signals together.

## Moving Pattern

The person shouldn't moving randomly. A moving pattern should be used, presented to be a decision tree with probabilities. And the robot's task is to find the tree from experience. 

However, it's cost to interpret on Gazebo. Luckily, the environment is so simple that the procedure can be simulated on a matrix, just like an OI problem. So we can 'pretend' to learn a moving pattern by writing a small visible demo illustrating the learning procedure for presentation and insert the human's moving pattern to the robot's inherent decision. Then the robot will move by drawing samples from the tree's probability distribution randomly.
