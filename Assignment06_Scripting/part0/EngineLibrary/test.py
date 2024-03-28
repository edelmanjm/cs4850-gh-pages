import rose

renderer = rose.Renderer(640, 480)
scene = rose.PythonScene(renderer)
application = rose.Application(renderer)
application.setScene(scene)
application.loop(120)
