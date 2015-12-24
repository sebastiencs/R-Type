#include "Chat.hh"
#include "Transformation.hh"
#include "IGraphicEngine.hh"
#include "TaskScheduler.hh"
#include "Sprite.hh"
#include "Box.hh"
#include "Text.hh"
#include "TextField.hh"

Chat::Chat(const Transformation & t, IGraphicEngine * engine) :
	engine(engine),
	updated(true)
{
	_transformation = t;
	chatBackground = new Sprite("chatBackground.png", _transformation, engine);
	_transformation.setBounds(chatBackground->getTransformation().getWidth(), chatBackground->getTransformation().getHeight());
	chatBox = new Box(Orientation::vertical, _transformation, "chatBox");
	chatBox->setSpacing(10);

	userTextField = new TextField("",
		Transformation(_transformation.getX() + 5, _transformation.getY() - 15 + chatBackground->getTransformation().getHeight() - 20),
		10,
		DEFAULT_FONT,
		Color::White,
		"userTextField",
		engine);
	textEnteredCallback tptr = std::bind(&Chat::getText, this, std::placeholders::_1);
	engine->setTextEnteredCallback(tptr);

	messageReceiver = new TaskScheduler([&](void*) {		// check if a new message is pending every x ms
		std::string text = "";
		// HERE: NETWORK CODE
		text = "coucou";
		text = text.substr(0, STRING_SIZE_LIMIT);
		// !
		newLogs.push_back(text);
		updated = false;
		return nullptr;
	},
		50
		);
}

Chat::~Chat()
{
	if (messageReceiver) {
		messageReceiver->stop();
		delete messageReceiver;
	}
	if (chatBackground)
		delete chatBackground;
	if (chatBox)
		delete chatBox;
	if (userTextField)
		delete userTextField;
	engine->setTextEnteredCallback(nullptr);
}

void Chat::draw()
{
	chatBackground->draw();
	if (!updated) {
		for (std::string txt : newLogs) {
			addMessageToBox(txt);
			logs.push_back(txt);
		}
		newLogs.clear();
		updated = true;
	}
	chatBox->draw();
	userTextField->draw();
}

void Chat::addMessageToBox(const std::string & text)
{
	if (chatBox->getElements().size() > MESSAGE_COUNT_LIMIT) {
		Drawable* d = chatBox->getElement("Text" + logs.front());
		if (d) {
			chatBox->removeDrawable(d);
			delete d;
			logs.pop_front();
		}
	}
	Text* dText = new Text(text, DEFAULT_FONT, 10, Transformation(0, 0), engine);
	dText->setId("Text" + text);
	chatBox->addDrawable(dText);
}

void Chat::getText(const char c)
{
	static auto validChar = [](const char c) -> bool {
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ');
	};

	if (c == '\b') {
		std::string tmp = userTextField->getText();
		userTextField->setText(tmp.substr(0, tmp.size() - 1));
	}
	else if (c == '\n' || c == '\r') {
		// HERE: NETWORK CODE (remove below and do everything through network?)
		newLogs.push_back(userTextField->getText());
		updated = false;
		userTextField->setText("");
		// !
	}
	else if (validChar(c) && userTextField->getText().size() < STRING_SIZE_LIMIT)
		userTextField->setText(userTextField->getText() + c);
}
