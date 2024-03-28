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

left = rose.SDL_FRect(-1, 0, 1, h)
right = rose.SDL_FRect(w + 1, 0, 1, h)
top = rose.SDL_FRect(0, -1, w, 1)
bottom = rose.SDL_FRect(0, h + 1, w, 1)


def on_update(delta_time: float):
    if rose.SDL_FRect.intersects(ball.get_transform(), left):
        ball.set_velocity(speed, 0)
    elif rose.SDL_FRect.intersects(ball.get_transform(), right):
        ball.set_velocity(-speed, 0)


scene.set_on_update(on_update)

application = rose.Application(renderer)
application.set_scene(scene)
application.loop(120)
