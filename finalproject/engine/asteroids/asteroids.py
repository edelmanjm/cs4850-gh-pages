import random
from enum import Enum
import json
import math
from typing import List, NamedTuple
import sys
from xml.etree import ElementTree

sys.path.append('../cmake-build-debug')
sys.path.append('../release')
import rose

scaling: float
with open("config.json") as json_data:
    config = json.load(json_data)
    scaling = config['scaling']

# Make the hitbox smaller to avoid "unfair" collisions
hitbox_margin = 2 * scaling


def rotate_svg(svg_string, center_x, center_y, angle):
    # Namespace needs to be set first, see https://stackoverflow.com/questions/8983041/
    ElementTree.register_namespace("", "http://www.w3.org/2000/svg")

    root = ElementTree.fromstring(svg_string)
    # Unsupported by https://github.com/memononen/nanosvg, which is the underlying library used by SDL_image.
    # The center must therefore be passed manually
    # root.set('transform-origin', 'center')
    root.set('transform', f'rotate({angle} {center_x} {center_y})')
    rotated_svg = ElementTree.tostring(root, encoding='unicode')

    return rotated_svg


class RockSizeData(NamedTuple):
    dims: float
    speed: float
    score: int


class Rock:
    sprites: List[str] = [f'assets/asteroid-{i}.svg' for i in range(3)]

    class Size(Enum):
        SMALL = RockSizeData(dims=8 * scaling, speed=40 * scaling, score=100)
        MEDIUM = RockSizeData(dims=16 * scaling, speed=20 * scaling, score=50)
        BIG = RockSizeData(dims=32 * scaling, speed=10 * scaling, score=20)

    def __init__(self, renderer, x, y, screen_w, screen_h, speed_multiplier, size: Size = Size.BIG):
        self.size = size
        self.underlying = rose.CollidingRectangleEntity()

        dims, speed, score = size.value
        speed *= speed_multiplier

        self.underlying.add_required(
            rose.FRect(-dims / 2 + hitbox_margin, -dims / 2 + hitbox_margin, dims / 2 - hitbox_margin,
                       dims / 2 - hitbox_margin), False)
        self.underlying.add_component(rose.TransformWrappingComponent(rose.FRect(0.0, 0.0, screen_w, screen_h)))
        sprite = random.choice(self.sprites)
        self.underlying.add_component(rose.TextureComponent(rose.ResourceManager.load_image(renderer.wrapped, sprite),
                                                            rose.FRect(-dims / 2, -dims / 2, dims / 2, dims / 2)))

        angle = random.random() * math.pi * 2
        self.underlying.set_velocity(math.cos(angle) * speed, math.sin(angle) * speed)
        self.underlying.set_transform(rose.Homogr().set_translation(x, y))


class Asteroids:
    projectiles: List[rose.CollidingRectangleEntity] = []
    rocks: List[Rock] = []
    scene_index = config['scene_index_start']
    lives: int
    score: int

    def __init__(self):
        self.scene_config = None
        self.w = 375 * scaling
        self.h = 246 * scaling

        self.renderer = rose.Renderer(self.w, self.h)

        self.player_speed = 100 * scaling
        self.player_rotation_speed = 180

        self.projectile_speed = 125 * scaling
        self.fire_debounce_time = 0.25
        self.should_fire = False
        self.time_since_last_fire = self.fire_debounce_time

        self.player = rose.CollidingRectangleEntity()
        player_width = 24 * scaling
        player_height = 16 * scaling
        hitbox_width = player_width - hitbox_margin
        hitbox_height = player_height
        self.player.add_required(rose.FRect(-hitbox_width / 2, -hitbox_height / 2, hitbox_width / 2, hitbox_height /
                                            2), False)
        self.player.add_component(rose.TransformWrappingComponent(rose.FRect(0, 0, self.w, self.h)))
        self.player.add_input_handler(lambda delta_time, keys: self.on_input(delta_time, keys))

        print("Loading player textures... (this may take a bit)", flush=True)
        with open("assets/ship-firing.svg", "r") as f:
            player_sprite: str = f.read()
            self.rotated_player_textures_firing = [
                rose.ResourceManager.load_svg(self.renderer.wrapped, rotate_svg(player_sprite, 32, 32, degrees))
                for degrees in range(360)]
        with open("assets/ship-static.svg", "r") as f:
            player_sprite: str = f.read()
            self.rotated_player_textures_static = [
                rose.ResourceManager.load_svg(self.renderer.wrapped, rotate_svg(player_sprite, 32, 32, degrees))
                for degrees in range(360)]
        print("Done!")
        self.player_texture = rose.TextureComponent(self.rotated_player_textures_static[0],
                                                    rose.FRect(-player_width / 2, -player_width / 2, player_width / 2,
                                                               player_width / 2))
        self.player.add_component(self.player_texture)
        self.accelerating = False
        self.rotate_player(-90)

        self.scene = rose.PythonScene(self.renderer)
        self.scene.add_entity(self.player)

        self.score_display = rose.TextEntity("assets/hyperspace.ttf", 16 * scaling, rose.SDL_Color(255, 255, 255, 255))
        self.score_display.add_required()
        self.score_display.set_transform(rose.Homogr().set_translation(16 * scaling, 0))
        self.set_score(0)
        self.scene.add_entity(self.score_display)

        self.lives_display = rose.TextEntity("assets/hyperspace.ttf", 8 * scaling, rose.SDL_Color(255, 255, 255, 255))
        self.lives_display.add_required()
        self.lives_display.set_transform(rose.Homogr().set_translation(16 * scaling, 24 * scaling))
        self.set_lives(config['lives'])
        self.scene.add_entity(self.lives_display)

        self.reset()

        self.scene.set_on_update(lambda delta_time: self.on_update(delta_time))

        self.application = rose.Application(self.renderer)
        self.application.set_scene(self.scene)

    def set_score(self, score):
        self.score = score
        self.score_display.text = f"Score:{self.score}"

    def set_lives(self, lives):
        self.lives = lives
        self.lives_display.text = f"Lives:{self.lives}"

    def add_rock(self, r):
        self.rocks.append(r)
        self.scene.add_entity(r.underlying)

    def add_projectile(self, p):
        self.projectiles.append(p)
        self.scene.add_entity(p)

    def remove_rock(self, r):
        self.rocks.remove(r)
        self.scene.remove_entity(r.underlying)

        self.set_score(self.score + r.size.value.score)

    def remove_projectile(self, p):
        self.projectiles.remove(p)
        self.scene.remove_entity(p)

    def reset_player(self):
        self.player.set_transform(rose.Homogr().set_translation(self.w / 2, self.h / 2))
        self.player.set_velocity(0, 0)
        self.should_fire = False

    def reset(self):
        with open(f"scenes/scene_{self.scene_index}.json") as json_data:
            self.scene_config = json.load(json_data)

        self.reset_player()

        for rock in self.rocks:
            self.scene.remove_entity(rock.underlying)
        for projectile in self.projectiles:
            self.scene.remove_entity(projectile)
        self.rocks = []
        self.projectiles = []

        for i in range(self.scene_config['initial_rock_count']):
            keepout_size = 50 * scaling
            x = self.w / 2
            y = self.h / 2
            while abs(x - self.w / 2) < keepout_size:
                x = random.randrange(0, int(self.w))
            while abs(y - self.h / 2) < keepout_size:
                y = random.randrange(0, int(self.h))
            r = Rock(self.renderer, x, y, self.w, self.h, self.scene_config['rock_speed_multiplier'], Rock.Size.BIG)
            self.add_rock(r)

    def split_rock(self, rock):
        next_size: Rock.Size | None
        match rock.size:
            case Rock.Size.BIG:
                next_size = Rock.Size.MEDIUM
            case Rock.Size.MEDIUM:
                next_size = Rock.Size.SMALL
            case _:
                next_size = None

        if next_size is None:
            print(f"Error: Cannot split rock of size {rock.size}")

        location = rock.underlying.get_transformed_origin()

        children_count = 2
        for i in range(children_count):
            self.add_rock(Rock(self.renderer, location.x, location.y, self.w, self.h, self.scene_config[
                'rock_speed_multiplier'], next_size))
        self.remove_rock(rock)

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

        self.add_projectile(projectile)

    def rotate_player(self, degrees):
        """
        :param degrees: The amount of additional rotation to apply to the player, in degrees.
        :return: Nothing
        """
        # Round it for sprite reasons
        rounded_transformation = round(degrees)
        self.player.rotate(math.radians(rounded_transformation))
        rounded_new = round(math.degrees(self.player.get_rotation()))
        if self.accelerating:
            self.player_texture.set_texture(self.rotated_player_textures_firing[rounded_new % 360])
        else:
            self.player_texture.set_texture(self.rotated_player_textures_static[rounded_new % 360])

    def on_input(self, delta_time: float, keys: List[int]):
        # TODO either import the SDL_Scancode enum, or find an equivalent in python
        if keys[82]:
            velocity_x, velocity_y = self.player.get_velocity()
            self.player.set_velocity(velocity_x + math.cos(self.player.get_rotation()) * self.player_speed * delta_time,
                                     velocity_y + math.sin(self.player.get_rotation()) * self.player_speed * delta_time)
            # Hacky way of switching sprites
            self.accelerating = True
            self.rotate_player(0)
        else:
            self.accelerating = False
            self.rotate_player(0)

        if keys[79]:
            self.rotate_player(self.player_rotation_speed * delta_time)
        elif keys[80]:
            self.rotate_player(-self.player_rotation_speed * delta_time)

        # Spacebar
        if keys[44]:
            # IDK why but calling fire directly results in a segfault, so we'll just defer the call
            self.should_fire = True

    def on_update(self, delta_time: float):
        if len(self.rocks) == 0:
            self.scene_index += 1
            if self.scene_index > config['scene_index_end']:
                print("You won!")
                exit(0)
            else:
                print(f"Advancing to level {self.scene_index + 1}...")
            self.reset()

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
                    if rock.size == Rock.Size.SMALL:
                        self.scene.remove_entity(rock.underlying)
                        self.rocks.remove(rock)
                    else:
                        self.split_rock(rock)
                    self.remove_projectile(projectile)

        for rock in self.rocks:
            if rose.CollidingRectangleEntity.intersects(rock.underlying, self.player):
                self.set_lives(self.lives - 1)
                if self.lives > 0:
                    self.reset_player()
                else:
                    print(f"Game over! You scored {self.score}")
                    exit(0)


asteroids = Asteroids()
asteroids.application.loop(120)
