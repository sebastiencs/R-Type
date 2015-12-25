#ifndef CHAT_HH_
# define CHAT_HH_

# include <memory>
# include "Drawable.hpp"
# include "ListSecure.hh"
# include "TaskScheduler.hh"
# include "Sprite.hh"
# include "Box.hh"
# include "Text.hh"
# include "TextField.hh"
# include "Transformation.hh"
# include "IGraphicEngine.hh"
# include "Box.hh"
# include "Sprite.hh"
# include "TaskScheduler.hh"
# include "TextField.hh"

class TaskScheduler;
class IGraphicEngine;
class Sprite;
class Box;
class TextField;

# define STRING_SIZE_LIMIT 30
# define MESSAGE_COUNT_LIMIT 25

using IGraphicEngine_SharedPtr = std::shared_ptr<IGraphicEngine>;

class Chat : public Drawable
{
public:
	Chat(const Transformation& t, IGraphicEngine_SharedPtr &engine);
	virtual ~Chat();

	// Drawable
	void draw();

private:
	void addMessageToBox(const std::string& text);
	void getText(const char c);

protected:
	ListSecure<std::string> logs;
	ListSecure<std::string> newLogs;
	TaskScheduler_SharedPtr messageReceiver;
	IGraphicEngine_SharedPtr engine;
	Sprite_SharedPtr chatBackground;
	Box_SharedPtr chatBox;
	TextField_SharedPtr userTextField;
	bool updated;
};

using Chat_UniquePtr = std::unique_ptr<Chat>;

#endif /* !CHAT_HH_*/
