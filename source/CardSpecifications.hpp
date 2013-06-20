#ifndef CARDSPECIFICATIONS_HPP
#define CARDSPECIFICATIONS_HPP

class CardSpecifications
{
public:
    CardSpecifications();
    CardSpecifications(const CardSpecifications& other);
    ~CardSpecifications();

    inline float width() const { return _width; }
    inline float height() const { return _height; }
    inline float depth() const { return _depth; }
    inline float cornerRadius() const { return _cornerRadius; }
    inline int cornerDetail() const { return _cornerDetail; }

    void width(float w);
    void height(float h);
    void depth(float d);
    void cornerRadius(float cr);
    void cornerDetail(int cd);

private:
    float _width;
    float _height;
    float _depth;
    float _cornerRadius;
    int _cornerDetail;
};

#endif
