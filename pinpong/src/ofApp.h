#pragma once

#include "ofMain.h"

class Figure {
public: 
	Figure(ofVec2f pos, ofVec2f speed) {
		m_pos = pos;
		m_speed = speed;
	};
	ofVec2f getSpeed() const { return m_speed; }
	ofVec2f getPos() const { return m_pos; }
	void setPos(ofVec2f pos) { m_pos = pos; }
	void setSpeed(ofVec2f s) { m_speed = s; }
	void invertSpeedX() { m_speed.x = -m_speed.x; }
	void invertSpeedY() { m_speed.y = -m_speed.y; }
private:
	ofVec2f m_speed;
	ofVec2f m_pos;
};

class Ball : public Figure {
public:
	Ball(ofVec2f pos, ofVec2f speed, int r);
	void draw() const;
	void setup();
	void update(ofVec2f pos1, ofVec2f size1, ofVec2f posPlayer, ofVec2f sizePlayer);
	int getRadius() const { return m_radius; }
	void setRadius(int r) { m_radius = r; }
private:
	int m_radius;
};

class Rect : public Figure {
public:
	Rect(ofVec2f pos, ofVec2f speed, ofVec2f size, bool player);
	void draw() const;
	void setup();
	void update(ofVec2f ballpos, int radius);
	void setSize(ofVec2f size) { m_size = size; }
	ofVec2f getSize() const { return m_size; }
	bool isPlayer() const { return m_player; }
	void keyLeft();
	void keyRight();
private:
	ofVec2f m_size;
	bool m_player;
};

class ofApp : public ofBaseApp{
	enum GameState{
		Menu,
		Game
	};
	enum Select {
		Play,
		Exit
	};
	public:
		void setup();
		void startGame();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		Rect *rect;
		Rect *rectPlayer;
		Ball *ball;
		GameState state;
		Select currentSelection;
		ofTrueTypeFont	verdana14;
		ofTrueTypeFont	verdana30;
		int scoreComp;
		int scorePlayer;
};
