#ifndef CHAT_HH_
# define CHAT_HH_

# include "Drawable.hpp"
# include "ListSecure.hh"

class TaskScheduler;
class IGraphicEngine;
class Sprite;
class Box;
class TextField;

# define STRING_SIZE_LIMIT 30
# define MESSAGE_COUNT_LIMIT 25

class Chat : public Drawable
{
public:
	Chat(const Transformation& t, IGraphicEngine* engine);
	virtual ~Chat();

	// Drawable
	void draw();

private:
	void addMessageToBox(const std::string& text);
	void getText(const char c);

protected:
	ListSecure<std::string> logs;
	ListSecure<std::string> newLogs;
	TaskScheduler* messageReceiver;
	IGraphicEngine* engine;
	Sprite* chatBackground;
	Box* chatBox;
	TextField* userTextField;
	bool updated;
};

#endif /* !CHAT_HH_*/