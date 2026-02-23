#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

class Renderer {
public:
  Renderer(int width, int height);
  ~Renderer();

  bool init();

  void draw();
  void render();

private:
  int m_width;
  int m_height;
};

#endif // !RENDERER_CLASS_H
