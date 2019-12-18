def draw_wall(m, th, tw, dh, dw):
	for i in range(th, th+dh):
		for j in range(tw, tw+dw):
			m[i+50][j+50] = 0
