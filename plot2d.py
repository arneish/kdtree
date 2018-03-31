from graphviz import Digraph
dot = Digraph(format='png')
vtx = open("plotdata.txt", 'r')
for line in vtx:
	line2=line.split(";")
	print(line2[0],line2[1].strip())
	dot.node(line2[0], line2[1].strip())
vtx.close()
edge = open("plotedges.txt", 'r')
counter = 0
for line in edge:
	#if (counter>20):
	#	break;
	counter+=1;
	line2 = line.split(",")
	print(line2[1])
	dot.edge(line2[0], line2[1].strip())
edge.close()
print(dot.source)

dot.render('GRAPH_2D', view=True) 
