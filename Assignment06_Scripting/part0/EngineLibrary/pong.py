import random
from enum import Enum
import math
from typing import List, NamedTuple
import sys

sys.path.append('./cmake-build-debug')
import rose


class Pong:
    class Score(NamedTuple):
        l: int
        r: int

    class XDirection(Enum):
        LEFT = 0
        RIGHT = 1

    class YDirection(Enum):
        UP = 0
        DOWN = 1

    def __init__(self):
        scaling = 2

        self.w = 375 * scaling
        self.h = 246 * scaling

        self.ball_speed = 350
        self.paddle_speed = 225
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

        self.score = Pong.Score(0, 0)
        self.score_display_l = rose.TextEntity("assets/bit5x3.ttf", 32 * scaling, rose.SDL_Color(255, 255, 255, 255))
        self.score_display_r = rose.TextEntity("assets/bit5x3.ttf", 32 * scaling, rose.SDL_Color(255, 255, 255, 255))
        self.score_display_l.add_required(rose.SDL_FRect(self.w / 3, 0, 0, 0))
        self.score_display_r.add_required(rose.SDL_FRect(self.w / 3 * 2, 0, 0, 0))

        self.scene.add_entity(self.score_display_l)
        self.scene.add_entity(self.score_display_r)

        self.reset(self.XDirection.RIGHT)

        self.scene.set_on_update(lambda delta_time: self.on_update(delta_time))

        self.application = rose.Application(renderer)
        self.application.set_scene(self.scene)

    def reset(self, serve_direction: XDirection):
        self.score_display_l.text = str(self.score.l)
        self.score_display_r.text = str(self.score.r)

        ball_y = random.randint(int(self.h / 3), int(self.h * 2 / 3))
        self.ball.set_transform(rose.SDL_FRect(self.w / 2 - self.ball_size / 2, ball_y,
                                               self.ball_size, self.ball_size))
        x_multiplier: float
        if serve_direction == self.XDirection.LEFT:
            x_multiplier = -1.0
        else:
            x_multiplier = 1.0
        self.ball.set_velocity(self.ball_speed * x_multiplier, (random.random() * 2 - 1) * self.ball_speed * 0.25)

        self.paddle_l.set_transform(rose.SDL_FRect(self.paddle_x, self.paddle_y, self.paddle_w, self.paddle_h))
        self.paddle_r.set_transform(rose.SDL_FRect(self.w - self.paddle_x - self.paddle_w, self.paddle_y,
                                                   self.paddle_w, self.paddle_h))

    def on_input(self, delta_time: float, keys: List[int]):
        # TODO either import the SDL_Scancode enum, or find an equivalent in python
        if keys[81]:
            self.move_paddle(delta_time, self.paddle_r, self.YDirection.UP)
        elif keys[82]:
            self.move_paddle(delta_time, self.paddle_r, self.YDirection.DOWN)

    def ai(self, delta_time: float):
        paddle = self.paddle_l
        difference = self.ball.get_transform().y - paddle.get_transform().y
        if difference > 4:
            self.move_paddle(delta_time, paddle, self.YDirection.UP)
        elif difference < -4:
            self.move_paddle(delta_time, paddle, self.YDirection.DOWN)

    def move_paddle(self, delta_time: float, paddle, direction: YDirection):
        transform = paddle.get_transform()
        if direction == self.YDirection.UP:
            new_y = min(transform.y + self.paddle_speed * delta_time, self.h - self.paddle_h)
            paddle.set_transform(rose.SDL_FRect(transform.x, new_y, transform.w, transform.h))
        else:
            new_y = max(transform.y - self.paddle_speed * delta_time, 0)
            paddle.set_transform(rose.SDL_FRect(transform.x, new_y, transform.w, transform.h))

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
            self.score = Pong.Score(self.score.l, self.score.r + 1)
            # Winner serves
            self.reset(self.XDirection.RIGHT)
        elif rose.SDL_FRect.intersects(self.ball.get_transform(), self.right):
            self.score = Pong.Score(self.score.l + 1, self.score.r)
            # Winner serves
            self.reset(self.XDirection.LEFT)
        elif (rose.SDL_FRect.intersects(self.ball.get_transform(), self.top)
              or rose.SDL_FRect.intersects(self.ball.get_transform(), self.bottom)):
            prev_velocity = self.ball.get_velocity()
            self.ball.set_velocity(prev_velocity[0], -prev_velocity[1])
        elif rose.CollidingRectangleEntity.intersects(self.ball, self.paddle_l):
            self.bounce(self.paddle_l, 1.0)
        elif rose.CollidingRectangleEntity.intersects(self.ball, self.paddle_r):
            self.bounce(self.paddle_r, -1.0)

        self.ai(delta_time)


pong = Pong()
pong.application.loop(120)
