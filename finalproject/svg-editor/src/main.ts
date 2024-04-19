import { SVG, Line } from '@svgdotjs/svg.js';

enum Endpoint {
  Start,
  End,
}

export function Draw() {
  const draw = SVG().addTo('#canvas').size(800, 600);
  const lines: Line[] = [];
  let isDrawing = false;
  let startX: number = 0;
  let startY: number = 0;
  let selectedLine: Line | null = null;
  let selectedEndpoint: Endpoint | null = null;

  // Function to calculate distance between two points
  const distance = (x1: number, y1: number, x2: number, y2: number) => {
    const dx = x2 - x1;
    const dy = y2 - y1;
    return Math.sqrt(dx * dx + dy * dy);
  };

  // Function to check if a point is close to a line endpoint
  const isCloseToEndpoint = (x: number, y: number, line: Line) => {
    const tolerance = 5; // Adjust this value to set the proximity tolerance
    return (
      distance(x, y, line.attr('x1'), line.attr('y1')) < tolerance ||
      distance(x, y, line.attr('x2'), line.attr('y2')) < tolerance
    );
  };

  const onMouseDown = (event: MouseEvent) => {
    const { offsetX, offsetY, button, altKey, ctrlKey, metaKey } = event;
    selectedLine = null;
    selectedEndpoint = null;

    for (const line of lines) {
      if (isCloseToEndpoint(offsetX, offsetY, line)) {
        selectedLine = line;
        selectedEndpoint =
          distance(offsetX, offsetY, line.attr('x1'), line.attr('y1')) <
          distance(offsetX, offsetY, line.attr('x2'), line.attr('y2'))
            ? Endpoint.Start
            : Endpoint.End;
        break;
      }
    }

    // Snap start to existing lines, if possible
    if (selectedLine && selectedEndpoint != null) {
      let id: string;
      switch (selectedEndpoint) {
        case Endpoint.Start:
          id = '1';
          break;
        case Endpoint.End:
          id = '2';
          break;
      }
      startX = selectedLine.attr(`x${id}`);
      startY = selectedLine.attr(`y${id}`);
    } else {
      startX = offsetX;
      startY = offsetY;
    }
    // Start drawing a new line if not near an existing endpoint
    isDrawing = true;
    const newLine = draw.line(startX, startY, startX, startY).stroke({ width: 2, color: 'black' });
    lines.push(newLine);
  };

  const onMouseMove = (event: MouseEvent) => {
    const { offsetX, offsetY } = event;

    if (isDrawing && lines.length > 0) {
      const currentLine = lines[lines.length - 1];
      currentLine.plot(startX, startY, offsetX, offsetY);
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
  };

  draw.node.addEventListener('mousedown', onMouseDown);
  draw.node.addEventListener('mousemove', onMouseMove);
  draw.node.addEventListener('mouseup', onMouseUp);
}

document.addEventListener('DOMContentLoaded', Draw);
