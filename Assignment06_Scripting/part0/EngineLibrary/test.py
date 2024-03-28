import sys
sys.path.append('./cmake-build-debug')
import rose


w = 640
h = 480
speed = 100

renderer = rose.Renderer(w, h)

ball = rose.CollidingRectangleEntity()
ball.add_required(rose.SDL_FRect(w / 2, h / 2, w / 20, w / 20))
ball.set_velocity(speed, 0)

player = rose.CollidingRectangleEntity()
player.add_required(rose.SDL_FRect(0, 0, w / 10, w / 20))

bot = rose.CollidingRectangleEntity()
bot.add_required(rose.SDL_FRect(w, 0, w / 10, w / 20))

scene = rose.PythonScene(renderer)
scene.add_entity(ball)
# scene.add_entity(player)
# scene.add_entity(bot)

# TODO add borders for collision


def on_update(delta_time: float):
    if ball.get_transform().x < 0:
        ball.set_velocity(speed, 0)
    elif ball.get_transform().x > w:
        ball.set_velocity(-speed, 0)


scene.set_on_update(on_update)

application = rose.Application(renderer)
application.set_scene(scene)
application.loop(120)
