import random
from collections import namedtuple
from enum import Enum
import math
from typing import List, NamedTuple
import sys

sys.path.append('./cmake-build-debug')
import rose

scaling = 2

SizeData = namedtuple('SizeData','dims speed')


class Rock:

    class Size(Enum):
        SMALL = SizeData(dims=10 * scaling, speed=40 * scaling)
        MEDIUM = SizeData(dims=20 * scaling, speed=20 * scaling)
        BIG = SizeData(dims=40 * scaling, speed=10 * scaling)

    def __init__(self, x, y, screen_w, screen_h, size: Size = Size.BIG):
        self.underlying = rose.CollidingRectangleEntity()

        dims, speed = size.value

        self.underlying.add_required(
            rose.FRect(-dims / 2, -dims / 2, dims / 2, dims / 2))
        self.underlying.add_component(rose.TransformWrappingComponent(rose.FRect(0, 0, screen_w, screen_h)))

        angle = random.random() * math.pi * 2
        self.underlying.set_velocity(math.cos(angle) * speed, math.sin(angle) * speed)
        self.underlying.set_transform(rose.Homogr().set_translation(x, y))


class Asteroids:

    projectiles: List[rose.CollidingRectangleEntity] = []
    rocks: List[Rock] = []
    initial_rock_count = 4

    def __init__(self):
        self.w = 375 * scaling
        self.h = 246 * scaling

        renderer = rose.Renderer(self.w, self.h)

        self.player_speed = 100 * scaling
        self.player_rotation_speed = math.radians(180)

        self.projectile_speed = 125 * scaling
        self.fire_debounce_time = 0.25
        self.should_fire = False
        self.time_since_last_fire = self.fire_debounce_time

        self.player = rose.CollidingRectangleEntity()
        player_size = 5 * scaling
        self.player.add_required(rose.FRect(-player_size / 2, -player_size / 2, player_size / 2, player_size / 2))
        self.player.add_component(rose.TransformWrappingComponent(rose.FRect(0, 0, self.w, self.h)))
        self.player.add_input_handler(lambda delta_time, keys: self.on_input(delta_time, keys))

        self.scene = rose.PythonScene(renderer)
        self.scene.add_entity(self.player)

        self.reset()

        self.scene.set_on_update(lambda delta_time: self.on_update(delta_time))

        self.application = rose.Application(renderer)
        self.application.set_scene(self.scene)

    def reset(self):
        self.player.set_transform(rose.Homogr().set_translation(self.w / 2, self.h / 2))
        self.player.set_velocity(0, 0)
        self.should_fire = False

        for i in range(self.initial_rock_count):
            x = random.randrange(0, self.w)
            y = random.randrange(0, self.h)
            r = Rock(x, y, self.w, self.h, Rock.Size.BIG)
            self.scene.add_entity(r.underlying)
            self.rocks.append(r)

    def fire(self):
        projectile = rose.CollidingRectangleEntity()
        projectile_size = 2 * scaling
        projectile.add_required(
            rose.FRect(-projectile_size / 2, -projectile_size / 2, projectile_size / 2, projectile_size / 2))
        projectile.add_component(rose.TransformWrappingComponent(rose.FRect(0, 0, self.w, self.h)))
        projectile.add_component(rose.LifetimeComponent(1000))
        velocity_x, velocity_y = self.player.get_velocity()
        velocity_x += math.cos(self.player.get_rotation()) * self.projectile_speed
        velocity_y += math.sin(self.player.get_rotation()) * self.projectile_speed
        projectile.set_velocity(velocity_x, velocity_y)
        projectile.set_transform(self.player.get_transform())
        self.scene.add_entity(projectile)

        self.projectiles.append(projectile)

    def on_input(self, delta_time: float, keys: List[int]):
        # TODO either import the SDL_Scancode enum, or find an equivalent in python
        if keys[82]:
            velocity_x, velocity_y = self.player.get_velocity()
            self.player.set_velocity(velocity_x + math.cos(self.player.get_rotation()) * self.player_speed * delta_time,
                                     velocity_y + math.sin(self.player.get_rotation()) * self.player_speed * delta_time)
        if keys[79]:
            self.player.rotate(self.player_rotation_speed * delta_time)
        elif keys[80]:
            self.player.rotate(-self.player_rotation_speed * delta_time)

        # Spacebar
        if keys[44]:
            # IDK why but calling fire directly results in a segfault, so we'll just defer the call
            self.should_fire = True

    def on_update(self, delta_time: float):
        if self.should_fire:
            if self.time_since_last_fire > self.fire_debounce_time:
                self.fire()
                self.should_fire = False
                self.time_since_last_fire = 0
            else:
                self.time_since_last_fire += delta_time

        # Remove dead projectiles
        for projectile in self.projectiles:
            if not projectile.renderable:
                self.scene.remove_entity(projectile)
        self.projectiles = list(filter(lambda p: p.renderable, self.projectiles))

        for projectile in self.projectiles:
            for rock in self.rocks:
                if rose.CollidingRectangleEntity.intersects(projectile, rock.underlying):
                    self.scene.remove_entity(rock.underlying)
                    self.rocks.remove(rock)


asteroids = Asteroids()
asteroids.application.loop(120)
