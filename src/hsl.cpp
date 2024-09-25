#include "hsl.h"

HSL::HSL(int color)
{
  // need to convert this to HSL form
  std::cout << color << std::endl;
}

HSL::HSL()
{
}

HSL::HSL(double hue, double saturation, double luminence)
{
  this->hue = hue;
  this->saturation = saturation;
  this->luminence = luminence;
}

double HSL::hueToRGB(double p, double q, double t)
{
  if (t < 0)
    t += 1;
  if (t > 1)
    t -= 1;
  if (t < 1. / 6)
    return p + (q - p) * 6 * t;
  if (t < 1. / 2)
    return q;
  if (t < 2. / 3)
    return p + (q - p) * ((double)2 / 3 - t) * 6;
  return p;
}

int HSL::toHex()
{
  double r, g, b;
  double h = this->hue;
  double s = this->saturation;
  double l = this->luminence;

  if (this->saturation == 0)
  {
    r = g = b = l;
  }

  else
  {
    const double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    const double p = 2 * l - q;
    r = this->hueToRGB(p, q, h + 1. / 3);
    g = this->hueToRGB(p, q, h);
    b = this->hueToRGB(p, q, h - 1. / 3);
  }

  int rgb[3] = {((int)std::round(r * 255)) << 16,
                ((int)std::round(g * 255)) << 8, (int)std::round(b * 255)};

  return rgb[0] | rgb[1] | rgb[2];
}

std::ostream &operator<<(std::ostream &out, const HSL &color)
{
  out << "[ H: " << color.hue << " S: " << color.saturation
      << " L: " << color.luminence << " ]";
  return out;
}

HSL HSL::modifyLuminence(double l)
{
  return HSL(this->hue, this->saturation, l);
}

HSL HSL::modifySaturation(double s)
{
  return HSL(this->hue, s, this->saturation);
}

HSL HSL::modifyHue(double h)
{
  return HSL(h, this->saturation, this->saturation);
}
