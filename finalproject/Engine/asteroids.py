import random
from enum import Enum
import math
from typing import List, NamedTuple
import sys

sys.path.append('./cmake-build-debug')
import rose


class Asteroids:
    def __init__(self):
        scaling = 2

        self.w = 375 * scaling
        self.h = 246 * scaling

        renderer = rose.Renderer(self.w, self.h)

        self.player_speed = 100
        self.player_rotation_speed = math.radians(30)

        self.player = rose.CollidingRectangleEntity()
        player_size = 4 * scaling
        self.player.add_required(rose.SDL_FRect(self.w / 2, self.h / 2, player_size, player_size))
        self.player.add_input_handler(lambda delta_time, keys: self.on_input(delta_time, keys))

        self.scene = rose.PythonScene(renderer)
        self.scene.add_entity(self.player)

        self.reset()

        self.scene.set_on_update(lambda delta_time: self.on_update(delta_time))

        self.application = rose.Application(renderer)
        self.application.set_scene(self.scene)

    def reset(self):
        new_transform = self.player.get_transform()
        new_transform.move_to(self.w / 2, self.h / 2)
        self.player.set_transform(new_transform)
        self.player.set_velocity(0, 0)

    def on_input(self, delta_time: float, keys: List[int]):
        # TODO either import the SDL_Scancode enum, or find an equivalent in python
        if keys[82]:
            velocity_x, velocity_y = self.player.get_velocity()
            self.player.set_velocity(velocity_x + math.cos(self.player.heading) * self.player_speed * delta_time,
                                     velocity_y + math.sin(self.player.heading) * self.player_speed * delta_time)
        elif keys[79]:
            self.player.heading += self.player_rotation_speed * delta_time
        elif keys[80]:
            self.player.heading -= self.player_rotation_speed * delta_time

    def on_update(self, delta_time: float):
        pass


pong = Asteroids()
pong.application.loop(120)
