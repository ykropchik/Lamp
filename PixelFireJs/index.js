const WIDTH = 32;
const HEIGHT = 32;
const FPS = 60

document.addEventListener('DOMContentLoaded', initialize);

class HSV {
	constructor(h, s, v) {
		this.h = h < 0 ? 256 - h : h;
		this.s = s < 0 ? 256 - s : s;
		this.v = v < 0 ? 256 - v : v;
	}

	isNull() {
		return this.h === 0 && this.s === 0 && this.v === 0;
	}

	canonicalHSV() {
		return {
			h: map(0, 255, 0, 360, this.h),
			s: map(0, 255, 0, 100, this.s),
			v: map(0, 255, 0, 100, this.v)
		}
	}
}

class Fire {
	constructor(hue, sparkles) {
		this.hue = hue;
		this.sparkles = sparkles;
		this.matrixValue = getFilledMatrix(WIDTH, HEIGHT, 0);
		this.pixels = getFilledMatrix(WIDTH, HEIGHT, new HSV(0, 0, 0));
		this.pcnt = 0;
		this.line = [];

		this.generateLine();
	}

	static valueMask = [
		[32, 0, 0, 0, 0, 0, 0, 32, 32, 0, 0, 0, 0, 0, 0, 32],
		[64, 0, 0, 0, 0, 0, 0, 64, 64, 0, 0, 0, 0, 0, 0, 64],
		[96, 32, 0, 0, 0, 0, 32, 96, 96, 32, 0, 0, 0, 0, 32, 96],
		[128, 64, 32, 0, 0, 32, 64, 128, 128, 64, 32, 0, 0, 32, 64, 128],
		[160, 96, 64, 32, 32, 64, 96, 160, 160, 96, 64, 32, 32, 64, 96, 160],
		[192, 128, 96, 64, 64, 96, 128, 192, 192, 128, 96, 64, 64, 96, 128, 192],
		[255, 160, 128, 96, 96, 128, 160, 255, 255, 160, 128, 96, 96, 128, 160, 255],
		[255, 192, 160, 128, 128, 160, 192, 255, 255, 192, 160, 128, 128, 160, 192, 255]
	];

	static hueMask = [
		[1, 11, 19, 25, 25, 22, 11, 1, 1, 11, 19, 25, 25, 22, 11, 1],
		[1, 8, 13, 19, 25, 19, 8, 1, 1, 8, 13, 19, 25, 19, 8, 1],
		[1, 8, 13, 16, 19, 16, 8, 1, 1, 8, 13, 16, 19, 16, 8, 1],
		[1, 5, 11, 13, 13, 13, 5, 1, 1, 5, 11, 13, 13, 13, 5, 1],
		[1, 5, 11, 11, 11, 11, 5, 1, 1, 5, 11, 11, 11, 11, 5, 1],
		[0, 1, 5, 8, 8, 5, 1, 0, 0, 1, 5, 8, 8, 5, 1, 0],
		[0, 0, 1, 5, 5, 1, 0, 0, 0, 0, 1, 5, 5, 1, 0, 0],
		[0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0]
	];

	generateLine() {
		for (let x = 0; x < WIDTH; x++) {
			this.line[x] = random(64, 255);
		}
	}

	shiftUp() {
		for (let y = HEIGHT - 1; y > 0; y--) {
			for (let x = 0; x < WIDTH; x++) {
				let newX = x;
				if (x > 15) newX = x % 16;
				if (y > 7) continue;
				this.matrixValue[y][newX] = this.matrixValue[y - 1][newX];
			}
		}

		for (let x = 0; x < WIDTH; x++) {
			let newX = x;
			if (x > 15) newX = x % 16;
			this.matrixValue[0][newX] = this.line[newX];
		}
	}

	createFrame() {
		if (this.pcnt >= 100) {
			this.shiftUp();
			this.generateLine();
			this.pcnt = 0;
		}

		this.generateMatrix();
		this.pcnt += 30;
	}

	generateMatrix() {
		let nextv;

		// each row interpolates with the one before it
		for (let y = HEIGHT - 1; y > 0; y--) {
			for (let x = 0; x < WIDTH; x++) {
				let newX = x;
				if (x > 15) newX = x % 16;
				if (y < 8) {
					nextv = (((100.0 - this.pcnt) * this.matrixValue[y][newX] +
							this.pcnt * this.matrixValue[y - 1][newX]) /
						100.0) - Fire.valueMask[y][newX];

					this.pixels[x][y] = new HSV(this.hue + Fire.hueMask[y][newX], 255, Math.max(0, nextv));
				} else if (y === 8 && this.sparkles) {
					if (random(0, 20) === 0 && !this.pixels[x][y - 1].isNull())
						this.pixels[x][y] = this.pixels[x][y - 1];
					else
						this.pixels[x][y] = new HSV(0, 0, 0);
				} else if (this.sparkles) {
					// старая версия для яркости
					if (!this.pixels[x][y - 1].isNull())
						this.pixels[x][y] = this.pixels[x][y - 1];
					else
						this.pixels[x][y] = new HSV(0, 0, 0);
				}
			}
		}

		// first row interpolates with the "next" line
		for (let x = 0; x < WIDTH; x++) {
			let newX = x;
			if (x > 15) newX = x % 16;
			this.pixels[x][0] = new HSV(this.hue + Fire.hueMask[0][newX], 255, (((100.0 - this.pcnt) * this.matrixValue[0][newX] + this.pcnt * this.line[newX]) / 100.0));
		}
	}

	drawNewFrame() {
		this.createFrame();

		const divPixels = Array.from(document.getElementsByClassName('pixel'));
		for (let x = 0; x < WIDTH; x++) {
			for (let y = 0; y < HEIGHT; y++) {
				const canonicalHSV = this.pixels[x][y].canonicalHSV();
				const rgb = colorsys.hsvToRgb(canonicalHSV);
				divPixels.at(-(y * WIDTH + x) - 1).style.backgroundColor = colorsys.stringify(rgb);
			}
		}
	}
}

function random(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

function map(minA, maxA, minB, maxB, value) {
	return Math.round((value - minA) / (maxA - minA) * (maxB - minB) + minB);
}

function getFilledMatrix(width, height, value) {
	const matrix = [];
	for (let y = 0; y < height; y++) {
		matrix[y] = [];
		for (let x = 0; x < width; x++) {
			matrix[y][x] = value;
		}
	}
	return matrix;
}

const fire = new Fire(10, true);

function initialize() {
	const root = document.getElementById("root");
	for (let i = 0; i < WIDTH*HEIGHT; i++) {
		const pixel = document.createElement("div");
		pixel.classList.add("pixel");
		root.appendChild(pixel);
	}

	document.getElementById("interval-id").innerText = setInterval(fire.drawNewFrame.bind(fire), 1000 / FPS);
}
