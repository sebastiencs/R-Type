//
// BonusMalus.hh for epitech in /home/bresci_b/R-Type
//
// Made by bresci_b
// Login   <bresci_b@epitech.eu>
//
// Started on  Fri Nov 13 00:37:48 2015 bresci_b
// Last update Fri Nov 13 00:37:48 2015 bresci_b
//

#ifndef BONUSMALUS_HH_
# define BONUSMALUS_HH_

# include <memory>
# include "Debug.hh"
# include "Object.hh"

class		BonusMalus : public Object
{
public:

  enum {
    LIFE,
    INTERVAL_SHOT,
    DOUBLE_SHOT,
    TRIPLE_SHOT
  };

  BonusMalus();
  BonusMalus(const uint8_t id, const uint8_t type, const uint8_t speed, const uint16_t x, const uint16_t y);
  virtual ~BonusMalus();

  uint8_t	getSpeed() const;
  void		setSpeed(const uint8_t speed);
  uint8_t	getType() const;
  void		setType(const uint8_t type);

private:
  uint8_t	_speed;
  uint8_t	_type;
};

typedef std::shared_ptr<BonusMalus> BonusMalus_SharedPtr;

#endif /* !BONUSMALUS_HH_ */
