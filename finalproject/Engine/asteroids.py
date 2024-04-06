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

        self.player = rose.CollidingRectangleEntity()
        player_size = 4 * scaling
        self.player.add_required(rose.SDL_FRect(self.w / 2, self.h / 2, player_size, player_size))

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
        # TODO move player
        pass

    def on_update(self, delta_time: float):
        pass


pong = Asteroids()
pong.application.loop(120)
