#ifndef BUTTON_H_
# define BUTTON_H_

# include "GraphicEngine.hh"

class Button
{
public:
  Button(const std::string& name = "Default");
  virtual ~Button();

  const bool& getButtonState() const;

  void setButtonState(bool isPressed);
  void drawButton(const Transformation& t);

private:
  bool _isPressed;
};

#endif /* BUTTON_H_ */