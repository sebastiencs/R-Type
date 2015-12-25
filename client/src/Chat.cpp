#include "Chat.hh"

Chat::Chat(const Transformation & t, IGraphicEngine_SharedPtr &eng) :
	engine(eng),
	updated(true)
{
	_transformation = t;
	chatBackground = std::make_shared<Sprite>("chatBackground.png", _transformation, std::move(engine));
	_transformation.setBounds(chatBackground->getTransformation().getWidth(), chatBackground->getTransformation().getHeight());
	chatBox = std::make_shared<Box>(Orientation::vertical, _transformation, "chatBox");
	chatBox->setSpacing(10);

	userTextField = std::make_shared<TextField>("",
		Transformation(_transformation.getX() + 5, _transformation.getY() - 15 + chatBackground->getTransformation().getHeight() - 20),
		10,
		DEFAULT_FONT,
		Color::White,
		"userTextField",
		eng);
	textEnteredCallback tptr = std::bind(&Chat::getText, this, std::placeholders::_1);
	eng->setTextEnteredCallback(tptr);

	messageReceiver = std::make_shared<TaskScheduler>([&](void*) {		// check if a new message is pending every x ms
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
	}
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
		auto &&d = chatBox->getElement("Text" + logs.front());
		if (d) {
			chatBox->removeDrawable(d);
			logs.pop_front();
		}
	}
	Text_SharedPtr dText = std::make_shared<Text>(text, DEFAULT_FONT, 10, Transformation(0, 0), std::move(engine));
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
