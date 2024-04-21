import { SVG, Line, Svg, NumberAlias } from '@svgdotjs/svg.js';
import * as assert from 'assert';
import { Pane } from 'tweakpane';

enum Endpoint {
  Start = 1,
  End = 2,
}

const params: { width: NumberAlias; height: NumberAlias; scale: number } = {
  width: 128,
  height: 128,
  scale: 2.0,
};

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
  const tolerance = 5 / params.scale;
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

  folder.addBinding(params, 'width', { label: 'Width', min: 1 }).on('change', ev => {
    draw.width(ev.value);
    containerElement.style.width = `${ev.value}px`;
  });

  folder.addBinding(params, 'height', { label: 'Height', min: 1 }).on('change', ev => {
    draw.height(ev.value);
    containerElement.style.height = `${ev.value}px`;
  });

  folder
    .addBinding(params, 'scale', { label: 'Scale', min: 0.1, max: 10, step: 0.1 })
    .on('change', ev => {
      containerElement.style.transform = `scale(${ev.value})`;
    });
}

export function Draw() {
  const containerElement = document.getElementById('container') as HTMLDivElement;
  containerElement.style.width = `${params.width}px`;
  containerElement.style.height = `${params.height}px`;
  const draw = SVG().size(params.width, params.height).addTo(containerElement);
  const lines: Line[] = [];
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
      newLine = draw.line(startX, startY, startX, startY).stroke({ width: 1, color: 'white' });
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
  setupDownloadButton(draw);
}

function setupDownloadButton(draw: Svg) {
  const downloadButton = document.getElementById('download') as HTMLButtonElement;
  downloadButton.addEventListener('click', () => {
    const svgContent = draw.svg();
    const blob = new Blob([svgContent], { type: 'image/svg+xml' });
    const url = URL.createObjectURL(blob);

    const a = document.createElement('a');
    a.href = url;
    a.download = 'drawing.svg';
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
  });
}

document.addEventListener('DOMContentLoaded', Draw);
