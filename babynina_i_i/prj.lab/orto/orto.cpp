﻿#include <iostream>

#include <iostream>

namespace geo2d {
	namespace orto {
		class Quad {
		public:
			Quad() = default;
			Quad(const Quad&) = default;
			~Quad() = default;

		};

		class Rect : public Quad {
		public:
			Rect() = default;
			Rect(const Rect&) = default;
			~Rect() = default;

		};

		class Rect : public Quad {
		public:
			Rect() = default;
			Rect(const Rect&) = default;
			~Rect() = default;

			Rect(double& x0, double& y0, double& height, double& width) {
				x_center_ = x0;
				y_center_ = y0;
				height_ = height;
				width_ = width;
			};

		public:
			double x_center_;
			double y_center_;
			double height_;
			double width_;
		};
	}
}