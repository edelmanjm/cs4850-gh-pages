from typing import NamedTuple

import sys

sys.path.append('./cmake-build-debug')
import rose


class Pong:
    class Score(NamedTuple):
        l: int
        r: int

    def __init__(self):
        scaling = 2

        self.w = 375 * scaling
        self.h = 246 * scaling

        self.speed = 100

        renderer = rose.Renderer(self.w, self.h)

        self.ball = rose.CollidingRectangleEntity()
        self.ball_size = 4 * scaling
        self.ball.add_required(rose.SDL_FRect(0, 0, 0, 0))

        self.paddle_w = 4 * scaling
        self.paddle_h = 16 * scaling
        self.paddle_x = 48 * scaling
        self.paddle_y = self.h / 2 - self.paddle_h / 2

        self.paddle_l = rose.CollidingRectangleEntity()
        self.paddle_l.add_required(rose.SDL_FRect(0, 0, 0, 0))

        self.paddle_r = rose.CollidingRectangleEntity()
        self.paddle_r.add_required(rose.SDL_FRect(0, 0, 0, 0))

        self.scene = rose.PythonScene(renderer)
        self.scene.add_entity(self.ball)
        self.scene.add_entity(self.paddle_l)
        self.scene.add_entity(self.paddle_r)

        self.left = rose.SDL_FRect(-1, 0, 1, self.h)
        self.right = rose.SDL_FRect(self.w + 1, 0, 1, self.h)
        self.top = rose.SDL_FRect(0, -1, self.w, 1)
        self.bottom = rose.SDL_FRect(0, self.h + 1, self.w, 1)

        self.reset()

        self.score = Pong.Score(0, 0)

        self.scene.set_on_update(lambda delta_time: self.on_update(delta_time))

        self.application = rose.Application(renderer)
        self.application.set_scene(self.scene)

    def reset(self):
        self.ball.set_position(rose.SDL_FRect(self.w / 2 - self.ball_size / 2, self.h / 2 - self.ball_size / 2,
                                              self.ball_size, self.ball_size))
        self.ball.set_velocity(self.speed, 0)

        self.paddle_l.set_position(rose.SDL_FRect(self.paddle_x, self.paddle_y, self.paddle_w, self.paddle_h))
        self.paddle_r.set_position(rose.SDL_FRect(self.w - self.paddle_x - self.paddle_w, self.paddle_y,
                                                  self.paddle_w, self.paddle_h))

    def on_update(self, delta_time: float):
        if rose.SDL_FRect.intersects(self.ball.get_transform(), self.left):
            self.score = Pong.Score(self.score.l + 1, self.score.r)
            self.reset()
        elif rose.SDL_FRect.intersects(self.ball.get_transform(), self.right):
            self.score = Pong.Score(self.score.l, self.score.r + 1)
            self.reset()
        elif rose.CollidingRectangleEntity.intersects(self.ball, self.paddle_l):
            # ball.set_velocity(speed * 2, 0)
            pass
        elif rose.CollidingRectangleEntity.intersects(self.ball, self.paddle_r):
            self.ball.set_velocity(-self.speed * 2, 0)


pong = Pong()
pong.application.loop(120)
