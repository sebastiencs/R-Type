
#ifndef PAQUETPLAYERSHOT_H_
# define PAQUETPLAYERSHOT_H_

# include "Paquet.hh"

class		PaquetPlayerShot : public Paquet
{
private:
	uint8_t	_id;
	uint8_t _playerID;
	uint8_t _type;
	uint8_t _x;
	uint8_t _y;

public:
	PaquetPlayerShot();
	PaquetPlayerShot(const Buffer &);
	PaquetPlayerShot(void *, size_t);
	virtual ~PaquetPlayerShot();

	void setType(const uint8_t&);
	void setPlayerID(const uint8_t&);
	void setPosition(const uint8_t&, const uint8_t&);

	const uint8_t& getType() const;
	const uint8_t& getPlayerID() const;
	const uint8_t& getX() const;
	const uint8_t& getY() const;

	void		createPaquet();
	void		parsePaquet();
};

std::ostream	&operator<<(std::ostream &, PaquetPlayerShot &);

#endif /* !PAQUETPLAYERSHOT_H_ */
