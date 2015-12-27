#include "Credits.hh"

Credits::Credits(IGraphicEngine_SharedPtr eng)
  : engine(std::move(eng))
{

  DEBUG_MSG("Credits created");
  
  authors.push_front(std::make_shared<TextField>("Developpement :", Transformation(250, 300 + 35 * 0), 32, "Fipps.otf", Color::White, "DevTitle", engine));
  authors.push_front(std::make_shared<TextField>("", Transformation(250, 300 + 35 * 1), 32, "Fipps.otf", Color::White, "DevTitle", engine));
  authors.push_front(std::make_shared<TextField>("                Sebastien Chapuis", Transformation(250, 300 + 35 * 2), 32, "Fipps.otf", Color::White, "DChapuis", engine));
  authors.push_front(std::make_shared<TextField>("                Barbis", Transformation(250, 300 + 35 * 3), 32, "Fipps.otf", Color::White, "DBarbis", engine));
  authors.push_front(std::make_shared<TextField>("                Bobo", Transformation(250, 300 + 35 * 4), 32, "Fipps.otf", Color::White, "DBobo", engine));
  authors.push_front(std::make_shared<TextField>("                Clement Da Silva", Transformation(250, 300 + 35 * 5), 32, "Fipps.otf", Color::White, "DKev", engine));
  authors.push_front(std::make_shared<TextField>("                Alex Dana", Transformation(250, 300 + 35 * 6), 32, "Fipps.otf", Color::White, "DAlex", engine));
  authors.push_front(std::make_shared<TextField>("", Transformation(250, 300 + 35 * 7), 32, "Fipps.otf", Color::White, "DevTitle", engine));
  authors.push_front(std::make_shared<TextField>("Graphisme:      ", Transformation(250, 300 + 35 * 8), 32, "Fipps.otf", Color::White, "GraphTitle", engine));
  authors.push_front(std::make_shared<TextField>("                Barbis", Transformation(250, 300 + 35 * 9), 32, "Fipps.otf", Color::White, "GBarbis", engine));
  authors.push_front(std::make_shared<TextField>("                Clement Da Silva", Transformation(250, 300 + 35 * 10), 32, "Fipps.otf", Color::White, "GKev", engine));
  authors.push_front(std::make_shared<TextField>("                Alex Dana", Transformation(250, 300 + 35 * 11), 32, "Fipps.otf", Color::White, "GAlex", engine));
}

Credits::~Credits()
{
  DEBUG_MSG("Credits deleted");
}

void Credits::draw()
{
	for (auto &t : authors)
		t->draw();
}
