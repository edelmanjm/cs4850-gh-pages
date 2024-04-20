import { SVG, Line, Svg, NumberAlias } from '@svgdotjs/svg.js';
import * as assert from 'assert';
import { Pane } from 'tweakpane';

enum Endpoint {
  Start = 1,
  End = 2,
}

function getCoords(line: Line, endpoint: Endpoint): { x: number; y: number } {
  return { x: line.attr(`x${endpoint}`), y: line.attr(`y${endpoint}`) };
}

// Function to calculate distance between two points
function distance(x1: number, y1: number, x2: number, y2: number): number {
  const dx = x2 - x1;
  const dy = y2 - y1;
  return Math.sqrt(dx * dx + dy * dy);
}

// Function to check if a point is close to a line endpoint
function isCloseToEndpoint(x: number, y: number, line: Line): Endpoint | null {
  const tolerance = 5; // Adjust this value to set the proximity tolerance
  for (const [key, value] of Object.entries(Endpoint)) {
    const endpoint = value as Endpoint;
    let coords = getCoords(line, endpoint);
    if (distance(x, y, coords.x, coords.y) < tolerance) {
      return endpoint;
    }
  }
  return null;
}

function setupTweakpane(draw: Svg, containerElement: HTMLDivElement) {
  const pane = new Pane();
  const folder = pane.addFolder({ title: 'Canvas Size' });

  const params: { width: NumberAlias; height: NumberAlias; scale: number } = {
    width: draw.width(),
    height: draw.height(),
    scale: 1.0,
  };

  folder.addBinding(params, 'width', { label: 'Width', min: 1 }).on('change', ev => {
    draw.width(ev.value);
    containerElement.style.width = ev.value.valueOf.length + 'px';
  });

  folder.addBinding(params, 'height', { label: 'Height', min: 1 }).on('change', ev => {
    draw.height(ev.value);
    containerElement.style.height = ev.value.valueOf.length + 'px';
  });

  folder
    .addBinding(params, 'scale', { label: 'Scale', min: 0.1, max: 10, step: 0.1 })
    .on('change', ev => {
      containerElement.style.transform = `scale(${ev.value})`;
    });
}

export function Draw() {
  const containerElement = document.getElementById('container') as HTMLDivElement;
  const draw = SVG().size(128, 128).css('border', '2px solid black').addTo(containerElement);
  const lines: Line[] = [];
  let isDrawing = false;
  let startX: number = 0;
  let startY: number = 0;
  let selectedLine: Line | null = null;
  let selectedEndpoint: Endpoint | null = null;
  let newLine: Line | null = null;

  const onMouseDown = (event: MouseEvent) => {
    const { offsetX, offsetY, button, altKey, ctrlKey, metaKey } = event;
    selectedLine = null;
    selectedEndpoint = null;

    for (const line of lines) {
      if (selectedEndpoint === null) {
        selectedEndpoint = isCloseToEndpoint(offsetX, offsetY, line);
        if (selectedEndpoint !== null) {
          selectedLine = line;
        }
      }
    }

    // If any of these keys are held, we want to move the existing lines instead of drawing a
    // new one
    if (!(altKey || ctrlKey || metaKey)) {
      // Snap start to existing lines, if possible
      if (selectedLine != null && selectedEndpoint != null) {
        const coords = getCoords(selectedLine, selectedEndpoint);
        startX = coords.x;
        startY = coords.y;
      } else {
        startX = offsetX;
        startY = offsetY;
      }
      // Start drawing a new line if not near an existing endpoint
      newLine = draw.line(startX, startY, startX, startY).stroke({ width: 2, color: 'black' });
    }
  };

  const onMouseMove = (event: MouseEvent) => {
    let { offsetX, offsetY } = event;

    // Snap start to existing lines, if possible
    for (const line of lines) {
      let endpoint = isCloseToEndpoint(offsetX, offsetY, line);
      if (endpoint != null) {
        const coords = getCoords(line, endpoint);
        offsetX = coords.x;
        offsetY = coords.y;
      }
    }

    if (newLine) {
      newLine.plot(startX, startY, offsetX, offsetY);
    } else if (selectedLine && selectedEndpoint != null) {
      // Move the selected endpoint
      switch (selectedEndpoint) {
        case Endpoint.Start:
          selectedLine.plot(offsetX, offsetY, selectedLine.attr('x2'), selectedLine.attr('y2'));
          break;
        case Endpoint.End:
          selectedLine.plot(selectedLine.attr('x1'), selectedLine.attr('y1'), offsetX, offsetY);
          break;
      }
    }
  };

  const onMouseUp = () => {
    isDrawing = false;
    selectedLine = null;
    selectedEndpoint = null;

    if (newLine != null) {
      lines.push(newLine);
    }
    newLine = null;
  };

  draw.node.addEventListener('mousedown', onMouseDown);
  draw.node.addEventListener('mousemove', onMouseMove);
  draw.node.addEventListener('mouseup', onMouseUp);

  setupTweakpane(draw, containerElement);
}

document.addEventListener('DOMContentLoaded', Draw);
