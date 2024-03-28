import sys
sys.path.append('./cmake-build-debug')
import rose

renderer = rose.Renderer(640, 480)

ball = rose.CollidingRectangleEntity()
ball.add_required()
ball.set_velocity(1, 0)

scene = rose.PythonScene(renderer)
scene.add_entity(ball)

application = rose.Application(renderer)
application.set_scene(scene)
application.loop(120)
