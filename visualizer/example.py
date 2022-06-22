import vpython as vp
ball=vp.sphere(pos=vp.vector(0,0,0),radius=0.5,color=vp.color.red)
while True:
	pass

# ball = vp.sphere(pos=vp.vector(0, 0, 0), radius=0.5, color=vp.color.red)
# ball.velocity = vp.vector(0, 0, 0)
# ball.mass = 1
# ball.force = vp.vector(0, 0, 0)
# ball.acceleration = vp.vector(0, 0, 0)
# ball.g = vp.vector(0, -9.8, 0)
# ball.dt = 0.01

# while True:
# 	ball.force = ball.mass * ball.g
# 	ball.acceleration = ball.force / ball.mass
# 	ball.velocity = ball.velocity + ball.acceleration * ball.dt
# 	ball.pos = ball.pos + ball.velocity * ball.dt
# 	vp.rate(100)
# 	vp.display.title = "x: %.2f, y: %.2f, z: %.2f" % (ball.pos.x, ball.pos.y, ball.pos.z)

# 	if ball.pos.y < 0:
# 		ball.pos.y = 0
# 		ball.velocity.y = 0
# 		ball.acceleration.y = 0
# 		ball.force.y = 0
# 		vp.rate(100)
# 		vp.display.title = "x: %.2f, y: %.2f, z: %.2f" % (ball.pos.x, ball.pos.y, ball.pos.z)


# 	if ball.pos.x < 0:
# 		ball.pos.x = 0
# 		ball.velocity.x = 0
# 		ball.acceleration.x = 0
# 		ball.force.x = 0
# 		vp.rate(100)
# 		vp.display.title = "x: %.2f, y: %.2f, z: %.2f" % (ball.pos.x, ball.pos.y, ball.pos.z)


# if ball.pos.x > 10:
# 	ball.pos.x = 10
# 	ball.velocity.x = 0
# 	ball.acceleration.x = 0
# 	ball.force.x = 0
# 	vp.rate(100)
# 	vp.display.title = "x: %.2f, y: %.2f, z: %.2f" % (ball.pos.x, ball.pos.y, ball.pos.z)


# 	if ball.pos.z < 0:
# 		ball.pos.z = 0
# 		ball.velocity.z = 0
# 		ball.acceleration.z = 0
# 		ball.force.z = 0
# 		vp.rate(100)
# 		vp.display.title = "x: %.2f, y: %.2f, z: %.2f" % (ball.pos.x, ball.pos.y, ball.pos.z)



# 	if ball.pos.z > 10:
# 		ball.pos.z = 10
# 		ball.velocity.z = 0
# 		ball.acceleration.z = 0
# 		ball.force.z = 0
# 		vp.rate(100)
# 		vp.display.title = "x: %.2f, y: %.2f, z: %.2f" % (ball.pos.x, ball.pos.y, ball.pos.z)


	
 



# /
# vp.scene.width = vp.scene.height = 600
# vp.scene.background = vp.color.white
# vp.scene.title = "Visualizer"
# vp.scene.autoscale = False
# vp.scene.center = vp.vector(0, 0, 0)
# vp.scene.range = 1
# vp.scene.forward = vp.vector(0, 0, -1)
# vp.scene.up = vp.vector(0, 1, 0)
# vp.scene.autoscale = False
# vp.scene.autocenter = False

# 

# class Visualizer:
#     def __init__(self):
#         self.objects = []
#         self.labels = []
#         self.texts = []
#         self.circles = []
#         self.spheres = []
#         self.cylinders = []
#         self.arrows = []
#         self.points = []
#         self.curves = []
#         self.surfaces = []
#         self.volumes = []
#         self.graphs = []
#         self.graphs_2d = []
#         self.graphs_3d = []

#     def add_object(self, obj):
#         self.objects.append(obj)

#     def add_label(self, label):
#         self.labels.append(label)

#     def add_text(self, text):
#         self.texts.append(text)

#     def add_circle(self, circle):
#         self.circles.append(circle)

#     def add_sphere(self, sphere):
#         self.spheres.append(sphere)

#     def add_cylinder(self, cylinder):
#         self.cylinders.append(cylinder)

#     def add_arrow(self, arrow):
#         self.arrows.append(arrow)

#     def add_point(self, point):
#         self.points.append(point)

#     def add_curve(self, curve):
#         self.curves.append(curve)

#     def add_surface(self, surface):
#         self.surfaces.append(surface)

#     def add_volume(self, volume):
#         self.volumes.append(volume)

#     def add_graph(self, graph):
#         self.graphs.append(graph)

#     def add_graph_2d(self, graph):
#         self.graphs_2d.append(graph)

#     def add_graph_3d(self, graph):
#         self.graphs_3d.append(graph)

#     def draw(self):
#         for obj in self.objects:
#             obj.draw()
#         for label in self.labels:
#             label.draw()
#         for text in self.texts:
#             text.draw()
#         for circle in self.circles:
#             circle.draw()
#         for sphere in self.spheres:
#             sphere.draw()
#         for cylinder in self.cylinders:
#             cylinder.draw()
#         for arrow in self.arrows:
#             arrow.draw()
#         for point in self.points:
#             point.draw()
#         for curve in self.curves:
#             curve.draw()
#         for surface in self.surfaces:
#             surface.draw()
#         for volume in self.volumes:
#             volume.draw()
#         for graph in self.graphs:
#             graph.draw()

#     def draw_2d(self):

#         for graph in self.graphs_2d:
#             graph.draw()

#     def draw_3d(self):
            
#             for graph in self.graphs_3d:
#                 graph.draw()

#     def clear(self):
#         for obj in self.objects:
#             obj.clear()
#         for label in self.labels:
#             label.clear()
#         for text in self.texts:
#             text.clear()
#         for circle in self.circles:
#             circle.clear()
#         for sphere in self.spheres:
#             sphere.clear()
#         for cylinder in self.cylinders:
#             cylinder.clear()
#         for arrow in self.arrows:
#             arrow.clear()
#         for point in self.points:
#             point.clear()
#         for curve in self.curves:
#             curve.clear()
#         for surface in self.surfaces:
#             surface.clear()
#         for volume in self.volumes:
#             volume.clear()
#         for graph in self.graphs:
#             graph.clear()

#     def clear_2d(self):
#         for graph in self.graphs_2d:
#             graph.clear()

#     def clear_3d(self):
#         for graph in self.graphs_3d:
#             graph.clear()

#     def clear_all(self):
#         self.clear()
#         self.clear_2d()
#         self.clear_3d()


# class Object:
#     def __init__(self):
#         self.vp_obj = None

#     def draw(self):
#         pass

#     def clear(self):
#         pass


# class Label(Object):
#     def __init__(self, text, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.label(text=text, pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.text = self.text
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Text(Object):

#     def __init__(self, text, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.text(text=text, pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.text = self.text
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Circle(Object):
    
#         def __init__(self, pos, radius, color=vp.color.black):
#             super().__init__()
#             self.vp_obj = vp.circle(pos=pos, radius=radius, color=color)
    
#         def draw(self):
#             self.vp_obj.pos = self.pos
#             self.vp_obj.radius = self.radius
#             self.vp_obj.color = self.color
    
#         def clear(self):
#             self.vp_obj.visible = False


# class Sphere(Object):
#     def __init__(self, pos, radius, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.sphere(pos=pos, radius=radius, color=color)
            
#         def draw(self):
#             self.vp_obj.pos = self.pos
#             self.vp_obj.radius = self.radius
#             self.vp_obj.color = self.color
    
#         def clear(self):
#             self.vp_obj.visible = False


# class Cylinder(Object):
#     def __init__(self, pos, axis, radius, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.cylinder(pos=pos, axis=axis, radius=radius, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.axis = self.axis
#         self.vp_obj.radius = self.radius
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Arrow(Object):
#     def __init__(self, pos, axis, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.arrow(pos=pos, axis=axis, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.axis = self.axis
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Point(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.points(pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Curve(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.curve(pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Surface(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.surface(pos=pos, color=color)
            
#         def draw(self):
#             self.vp_obj.pos = self.pos
#             self.vp_obj.color = self.color
    
#         def clear(self):
#             self.vp_obj.visible = False


# class Volume(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.volume(pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Graph(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.graph(pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Graph2D(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.graph(pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False


# class Graph3D(Object):
#     def __init__(self, pos, color=vp.color.black):
#         super().__init__()
#         self.vp_obj = vp.graph(pos=pos, color=color)

#     def draw(self):
#         self.vp_obj.pos = self.pos
#         self.vp_obj.color = self.color

#     def clear(self):
#         self.vp_obj.visible = False





