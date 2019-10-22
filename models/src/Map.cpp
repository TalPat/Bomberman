#include "../include/Map.hpp"

const sf::Vector2i DEFAULT_SIZE(17, 17);
const float DESTRUCTABLE_CHANCE = 0.1;

Map::Map()
	: _size(DEFAULT_SIZE),
	  _tiles(this->_size.x * this->_size.y, Tile::Clear)
{
}

Map::~Map()
{
}

void Map::init(int level)
{
	std::srand(time(NULL));

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			this->_tiles[y * this->_size.x + x] = Tile::Clear;
			if (x == 0 || y == 0 || x == this->_size.x - 1 || y == this->_size.y - 1)
				this->_tiles[y * this->_size.x + x] = Tile::Solid;
			else if (x % 2 == 0 && y % 2 == 0)
				this->_tiles[y * this->_size.x + x] = Tile::Solid;
			else
			{
				if (static_cast<float>(rand()) / RAND_MAX < DESTRUCTABLE_CHANCE)
					this->_tiles[y * this->_size.x + x] = Tile::Destructible;
			}
		}
	}

	// Player starting cells
	this->_tiles[1 * this->_size.x + 1] = Tile::Clear;
	this->_tiles[1 * this->_size.x + 2] = Tile::Clear;
	this->_tiles[2 * this->_size.x + 1] = Tile::Clear;
}

bool Map::collide(const sf::Vector2f &pos, float hw, bool (*comp)(Tile)) const
{
	typedef sf::Vector2i v2i;
	typedef sf::Vector2f v2f;

	Tile t1 = this->tileAt(v2i(pos + v2f(-hw, -hw)));
	Tile t2 = this->tileAt(v2i(pos + v2f(-hw, +hw)));
	Tile t3 = this->tileAt(v2i(pos + v2f(+hw, -hw)));
	Tile t4 = this->tileAt(v2i(pos + v2f(+hw, +hw)));

	if (comp(t1) || comp(t2) || comp(t3) || comp(t4))
		return true;
	return false;
}

bool Map::lerpCollide(sf::Vector2f &pos, sf::Vector2f mv, float hw, bool (*comp)(Tile)) const
{
	for (float i = 1.0; i > 0.1; i *= 0.75)
	{
		sf::Vector2f newPos = pos + (i * mv);
		if (!this->collide(newPos, hw, comp)) {
			pos = newPos;
			return true;
		}
	}
	return false;
}

Tile Map::tileAt(sf::Vector2i pos) const
{
	return this->_tiles[pos.y * this->_size.x + pos.x];
}

void Map::setTile(sf::Vector2i pos, Tile tile)
{
	this->_tiles[pos.y * this->_size.x + pos.x] = tile;
}

const sf::Vector2i &Map::size() const
{
	return this->_size;
}

std::string Map::to_string()
{
	std::ostringstream sstream;

	sstream << this->_size.x << " "
			<< this->_size.y << " ";

	for (Tile tile : this->_tiles)
	{
		sstream << tile << " ";
	}
	sstream << '\n';

	return sstream.str();
}

void Map::from_string(std::istream &istream)
{
	this->_tiles.clear();
	istream >> this->_size.x >> this->_size.y;

	int length = this->_size.x * this->_size.y;
	for (int i = 0; i < length; i++)
	{
		int t;
		istream >> t;
		this->_tiles.push_back(Tile(t));
	}
}
