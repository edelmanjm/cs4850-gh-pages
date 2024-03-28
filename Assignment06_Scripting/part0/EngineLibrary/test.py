import sys
sys.path.append('./cmake-build-debug')
import rose

scaling = 2

w = 375 * scaling
h = 246 * scaling

speed = 100

renderer = rose.Renderer(w, h)

ball = rose.CollidingRectangleEntity()
ball_size = 4 * scaling
ball.add_required(rose.SDL_FRect(w / 2 - ball_size / 2, h / 2 - ball_size / 2, ball_size, ball_size))
ball.set_velocity(speed, 0)

paddle_w = 4 * scaling
paddle_h = 16 * scaling
paddle_x = 48 * scaling
paddle_y = h / 2 - paddle_h / 2

paddle_l = rose.CollidingRectangleEntity()
paddle_l.add_required(rose.SDL_FRect(paddle_x, paddle_y, paddle_w, paddle_h))

paddle_r = rose.CollidingRectangleEntity()
paddle_r.add_required(rose.SDL_FRect(w - paddle_x - paddle_w, paddle_y, paddle_w, paddle_h))

scene = rose.PythonScene(renderer)
scene.add_entity(ball)
scene.add_entity(paddle_l)
scene.add_entity(paddle_r)

left = rose.SDL_FRect(-1, 0, 1, h)
right = rose.SDL_FRect(w + 1, 0, 1, h)
top = rose.SDL_FRect(0, -1, w, 1)
bottom = rose.SDL_FRect(0, h + 1, w, 1)


def on_update(delta_time: float):
    if rose.SDL_FRect.intersects(ball.get_transform(), left):
        ball.set_velocity(speed, 0)
    elif rose.SDL_FRect.intersects(ball.get_transform(), right):
        ball.set_velocity(-speed, 0)
    elif rose.CollidingRectangleEntity.intersects(ball, paddle_l):
        ball.set_velocity(speed * 2, 0)
    elif rose.CollidingRectangleEntity.intersects(ball, paddle_r):
        ball.set_velocity(-speed * 2, 0)


scene.set_on_update(on_update)

application = rose.Application(renderer)
application.set_scene(scene)
application.loop(120)
