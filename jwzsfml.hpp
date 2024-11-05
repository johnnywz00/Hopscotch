#ifndef jwzsfml_hpp
#define jwzsfml_hpp


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "jwz.hpp"

using namespace sf;

#define ikp(k) if (sf::Keyboard::isKeyPressed(sf::Keyboard::k))
#define iKP(k) sf::Keyboard::isKeyPressed(sf::Keyboard::k)
#define iBP sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define vecU Vector2u
#define vecI Vector2i
#define vecF Vector2f
#define vecf Vector2f
#define vec3u Vector3u
#define vec3i Vector3i
#define vec3f Vector3f
#define gP getPosition
#define sP setPosition
#define gRot getRotation
#define sRot setRotation
#define gLB getLocalBounds
#define gGB getGlobalBounds
#define gTR getTextureRect
#define gVC getVertexCount
#define cO centerOrigin
#define VX(X, Y) Vertex(Vector2f(X, Y), Color::Black)
#define VXC(X, Y, C) Vertex(Vector2f(X, Y), C)

#define adjustVal(key, prop, inc, min, max) \
	ikp(key){ \
		if (iKP(LShift)) prop = decm(prop, inc, min); \
		else prop = incm(prop, inc, max); \
		PAUSE1; \
	}

    /* These values were hardcoded into hundreds of hours of my early work, 
     * specific to the laptop screen size I had at the time. Leave them
     * stand while this file acts as a shared header.
     */
constexpr int       ScrW = 1440;
constexpr int       ScrH = 900;
constexpr float     ScrCX = ScrW / 2;
constexpr float     ScrCY = ScrH / 2;

inline string vecfStr (vecF v, string tag = "") {
	
    string ret = "{" + fS(v.x) + ", " + fS(v.y) + "}";
    return tag.length() ? tag + ": " + ret : ret;
}

inline void centerOrigin (Shape& obj) {
	
    obj.setOrigin( 	obj.getLocalBounds().width/2,
    				obj.getLocalBounds().height/2 );
}

inline void centerOrigin (Sprite& obj) {
	
    obj.setOrigin( 	obj.getLocalBounds().width/2,
    				obj.getLocalBounds().height/2 );
}

inline void centerOrigin (Text& obj) {
	
    obj.setOrigin( 	obj.getLocalBounds().width/2,
    				obj.getLocalBounds().height/2 );
}


inline float hyp (vecF& v1, vecF& v2) {
	
    auto X = v2.x - v1.x;
    auto Y = v2.y - v1.y;
    return abs(sqrt(X * X + Y * Y));
}

inline float hyp (vecF& v) {
	
    return abs(sqrt( (v.x * v.x) + (v.y * v.y) ));
}


inline vecF toRect (vecF& vec) {
	
    vecF ret(cos(toRad(vec.y)) * vec.x, sin(toRad(vec.y)) * vec.x);
    if (abs(vec.y) == 90 || abs(vec.y) == 270)  
    	ret.x = 0;
    if (abs(vec.y) == 0 || abs(vec.y) == 180)  
    	ret.y = 0;
    if (vec.x < .000001) { 
    	ret.x = 0; 
    	ret.y = 0; 
    }
    return ret;
}

inline vecF toRect (float mag, float direc) {
	
    vecF ret(cosd(direc) * mag, sind(direc) * mag);
    if (abs(direc) == 90 || abs(direc) == 270)
        ret.x = 0;
    if (abs(direc) == 0 || abs(direc) == 180)
        ret.y = 0;
    if (mag<.000001) {
        ret.x = 0;
        ret.y = 0;
    }
    return ret;
}

    // to rectangular coordinates given a vector in radians
inline vecF toRRect (float mag, float direc) {
	
    vecF ret(cos(direc) * mag, sin(direc) * mag);
    if (mag < .000001) {
        ret.x = 0;
        ret.y = 0;
    }
    return ret;
}

inline vecF toPolar (vecF& vec) {
	
    double x = double(vec.x);
    double y = double(vec.y);
    double mag = hyp(x, y);
    double t = atan2(y, x);
    float direc = float(toDeg(t));
    if (direc < 0)
        direc += 360;
    return vecF(float(mag), direc);
}

inline vecF toPolar (float xx, float yy) {
	
    double x = double(xx);
    double y = double(yy);
    double mag = hyp(x, y);
    double t = atan2(y, x);
    float direc = float(toDeg(t));
    if (direc < 0)
        direc += 360;
    return vecF(float(mag), direc);
}

inline vecF toRPolar (vecF& vec) {
	
    double x = double(vec.x);
    double y = double(vec.y);
    double mag = hyp(x, y);
    double t = atan2(y, x);
    return vecF(float(mag), float(t));
}

inline void setVPos (Vertex& v, vecF pos) {
	
    v.position = pos;
}

inline Color randomColor () {
	
    int r = randRange(1, 255);
    int g = randRange(1, 255);
    int b = randRange(1, 255);
    return Color(r, g, b);
}

inline Color mixColors (Color& c1, Color& c2) {
	
	
    return Color( (c1.r + c2.r) / 2,
                  (c1.g + c2.g) / 2, 
                  (c1.b + c2.b) / 2, 
                  (c1.a + c2.a) / 2 );
}

inline Color addRed (Color& c, int inc=1) {
	
    Color col { c };
    col.r = incm(col.r, inc, 255);
    return col;
}

inline Color addGreen (Color& c, int inc=1) {
	
    Color col { c };
    col.g = incm(col.g, inc, 255);
    return col;
}

inline Color addBlue (Color& c, int inc=1) {
	
    Color col { c };
    col.b = incm(col.b, inc, 255);
    return col;
}


#define ORANGE Color(255, 127, 0)
#define ORANGE75 Color(255, 159, 63)
#define ORANGE50 Color(255, 191, 127)
#define PEACH Color(255, 191, 127)
#define MEDORANGE Color(191, 95, 0)
#define MEDORANGE75 Color(191, 119, 47)
#define MEDORANGE50 Color(191, 143, 95)
#define DKORANGE Color(127, 63, 0)
#define DKORANGE75 Color(127, 79, 31)
#define DKORANGE50 Color(127, 95, 63)
#define AZURE Color(0, 127, 255)
#define AZURE75 Color(63, 159, 255)
#define AZURE50 Color(127, 191, 255)
#define SKYBLUE Color(127, 191, 255)
#define MEDAZURE Color(0, 95, 91)
#define MEDAZURE75 Color(47, 119, 191)
#define MEDAZURE50 Color(95, 143, 191)
#define DKAZURE Color(0, 63, 127)
#define DKAZURE75 Color(31, 79, 127)
#define DKAZURE50 Color(63, 95, 127)
#define PURPLE Color(127, 0, 255)
#define PURPLE75 Color(159, 63, 255)
#define PURPLE50 Color(191, 127, 255)


#endif /* jwzsfml_hpp */
