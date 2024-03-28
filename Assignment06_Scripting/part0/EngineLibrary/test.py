import math
from typing import List, NamedTuple

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

        self.ball_speed = 350
        self.paddle_speed = 250
        self.max_bounce_angle = math.radians(75)

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
        self.paddle_r.add_input_handler(lambda delta_time, keys: self.on_input(delta_time, keys))

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
        self.ball.set_velocity(self.ball_speed, 0)

        self.paddle_l.set_position(rose.SDL_FRect(self.paddle_x, self.paddle_y, self.paddle_w, self.paddle_h))
        self.paddle_r.set_position(rose.SDL_FRect(self.w - self.paddle_x - self.paddle_w, self.paddle_y,
                                                  self.paddle_w, self.paddle_h))

    def on_input(self, delta_time: float, keys: List[int]):
        # TODO either import the SDL_Scancode enum, or find an equivalent in python
        transform = self.paddle_r.get_transform()
        if keys[81]:
            new_y = min(transform.y + self.paddle_speed * delta_time, self.h - self.paddle_h)
            self.paddle_r.set_position(rose.SDL_FRect(transform.x, new_y, transform.w, transform.h))
        elif keys[82]:
            new_y = max(transform.y - self.paddle_speed * delta_time, 0)
            self.paddle_r.set_position(rose.SDL_FRect(transform.x, new_y, transform.w, transform.h))

    def ai(self, paddle):
        transform = self.paddle_r.get_transform()

    def bounce(self, paddle, horizontal_multiplier: float):
        ball_y = self.ball.get_transform().y
        paddle_y = paddle.get_transform().y

        # The distance, in pixels, from the center of the paddle to the center of the ball
        relative_intersect = ball_y - paddle_y - self.paddle_h / 2 + self.ball_size / 2
        # [-1.0, 1.0] from the top to the bottom of the paddle
        normalized_intersect = relative_intersect / ((self.paddle_h + self.ball_size) / 2)
        bounce_angle = normalized_intersect * self.max_bounce_angle

        # self.ball.set_velocity(-self.ball_speed * math.cos(bounce_angle),
        #                        self.ball_speed * math.sin(bounce_angle))
        # Seems like Pong generally maintains horizontal velocity
        self.ball.set_velocity(self.ball_speed * horizontal_multiplier, self.ball_speed * math.sin(bounce_angle))

    def on_update(self, delta_time: float):
        if rose.SDL_FRect.intersects(self.ball.get_transform(), self.left):
            self.score = Pong.Score(self.score.l + 1, self.score.r)
            self.reset()
        elif rose.SDL_FRect.intersects(self.ball.get_transform(), self.right):
            self.score = Pong.Score(self.score.l, self.score.r + 1)
            self.reset()
        elif (rose.SDL_FRect.intersects(self.ball.get_transform(), self.top)
              or rose.SDL_FRect.intersects(self.ball.get_transform(), self.bottom)):
            prev_velocity = self.ball.get_velocity()
            self.ball.set_velocity(prev_velocity[0], -prev_velocity[1])
        elif rose.CollidingRectangleEntity.intersects(self.ball, self.paddle_l):
            self.bounce(self.paddle_l, 1.0)
        elif rose.CollidingRectangleEntity.intersects(self.ball, self.paddle_r):
            self.bounce(self.paddle_r, -1.0)


pong = Pong()
pong.application.loop(120)
