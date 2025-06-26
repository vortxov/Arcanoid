
class Block {
protected:
    sf::Sprite sprite_;
    int hitPoints_;
    bool destroyed_;
    Bonus bonus;

public:
    Block();
    virtual ~Block() = default;

    void SetRandomBonus(int random_number);
    Bonus& GetBonus() { return bonus; };


    virtual void hit();
    virtual bool isDestroyed() const;
    virtual bool shouldBallBounce() const = 0;

	void destroy() { destroyed_ = true; } // Принудительное разрушение кирпича

    void setPosition(float x, float y);
    void setTexture(const sf::Texture& texture);

    sf::Sprite getSprite() { return sprite_; };

    virtual void draw(sf::RenderWindow& window) const;
    sf::FloatRect getGlobalBounds() const;

};