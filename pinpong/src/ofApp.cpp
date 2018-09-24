#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	state = GameState::Menu;
	currentSelection = Select::Play;
	scoreComp = 0;
	scorePlayer = 0;
}

void ofApp::startGame()
{
	ball = new Ball(ofVec2f(ofGetWidth() / 2 - 80, ofGetHeight() - 60), ofVec2f(0, 0), 20);
	rect = new Rect(ofVec2f(ofGetWidth() / 2 - 100, 10), ofVec2f(0, 0), ofVec2f(200, 30), false);
	rectPlayer = new Rect(ofVec2f(ofGetWidth() / 2 - 100, ofGetHeight() - 40), ofVec2f(0, 0), ofVec2f(200, 30), true); //�������� �����������
}

//--------------------------------------------------------------
void ofApp::update(){
	if (state == GameState::Game) {   
		if (ball->getPos().y <= 0) {     //���� ������ �� ����� ����� �� ���� �� ���� ������ � ������ ���������(� ��������� ������� �� ������������� ������)
			++scorePlayer;
			ball->setSpeed(ofVec2f(0, 0));
		}
		if (ball->getPos().y >= ofGetHeight() - ball->getRadius()) {  //���� �� �����������
			++scoreComp;
			ball->setSpeed(ofVec2f(0, 0));
		}
		ball->update(rect->getPos(), rect->getSize(), rectPlayer->getPos(), rectPlayer->getSize());
		if (ball->getSpeed().x != 0) {     //��������� ���������� ���� ��� ��������
			rect->update(ball->getPos(), ball->getRadius());
		}
		rectPlayer->update(ball->getPos(), ball->getRadius());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (state == GameState::Game) {
		ofBackground(255, 255, 255);
		ofSetColor(0, 0, 0);
		ofDrawBitmapString("enemy: " + ofToString(scoreComp), 10, 10);  //����
		ofSetColor(0, 0, 0);
		ofDrawBitmapString("player: " + ofToString(scorePlayer), 10, 20);
		ball->draw();
		rect->draw();
		rectPlayer->draw();
	}
	else {    //����
		ofBackground(0, 0, 0);
		ofSetColor(0, 255, 0);
		int v14Size, v30Size;
		if (currentSelection == Select::Play) {   //����� ������ ����
			v14Size = 30;
			v30Size = 25;
		}
		else {
			v14Size = 25;
			v30Size = 30;
		}
		verdana14.load("verdana.ttf", v14Size, true, true);
		verdana14.drawString("Start", ofGetWidth() / 2 - 50, ofGetHeight() / 2 - 50);   //��������� ������� ����
		ofSetColor(0, 255, 0);
		verdana30.load("verdana.ttf", v30Size, true, true);
		verdana30.drawString("Exit", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (state == GameState::Game) {
		if (key == OF_KEY_LEFT) {  //����������
			rectPlayer->keyLeft();
		}
		else if (key == OF_KEY_RIGHT) {  //����������
			rectPlayer->keyRight();
		} 
		else if (key == 32 && ball->getSpeed() == ofVec2f(0,0)) {  //space ������ ������
			ball->setSpeed(ofVec2f(-5, -5));
		}
	}
	else {
		if (key == OF_KEY_UP && currentSelection == Select::Exit) {   //����� ������� ����
			currentSelection = Select::Play;
		}
		if (key == OF_KEY_DOWN && currentSelection == Select::Play) {  //����� ������� ����
			currentSelection = Select::Exit;
		}
		if (key == 13) {     //enter
			if (currentSelection == Select::Play) {  
				startGame();  //�������� �����������
				state = GameState::Game;   //������������ ���������
			}
			else {
				ofExit();   //����� �� ����
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (state == GameState::Game) {
		if (key == OF_KEY_LEFT || OF_KEY_RIGHT) {    //���������
			rectPlayer->setSpeed(ofVec2f(0, 0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

Ball::Ball(ofVec2f pos, ofVec2f speed, int r) : Figure(pos, speed)
{
	m_radius = r;   //�����������
}

void Ball::draw() const
{
	ofFill();    
	ofSetColor(150, 150, 150);   
	ofCircle(getPos().x, getPos().y, getRadius());  //������������ ����
}

void Ball::setup()
{

}

void Ball::update(ofVec2f pos1, ofVec2f size1, ofVec2f posPlayer, ofVec2f sizePlayer)
{
	if (getSpeed().x != 0) {     //���� �� ����� �� �����(�������� ����)
		float nextX = getPos().x + getSpeed().x;
		float nextY = getPos().y + getSpeed().y;
		if (nextX <= 0 || nextX >= ofGetWidth() - getRadius()) {  //�������� ������ �� ����� �� ������
			invertSpeedX();
		}

		if (getPos().y + getRadius() + getSpeed().y >= posPlayer.y &&   //�������� ���� �� ��������� ������ �� �������������� ������
			(getPos().x + getRadius() > posPlayer.x && getPos().x < posPlayer.x + sizePlayer.x)) {
			setPos(ofVec2f(getPos().x + getSpeed().x, posPlayer.y - getRadius()));
			invertSpeedY();
		}
		else if (getPos().y - getRadius() + getSpeed().y <= pos1.y + size1.y &&   //�������� ���� �� ��������� ����� �� �������������� ����������
			(getPos().x + getRadius() > pos1.x && getPos().x < pos1.x + size1.x)) {
			setPos(ofVec2f(getPos().x + getSpeed().x, pos1.y + size1.y + getRadius()));
			invertSpeedY();
		}
		else {
			setPos(ofVec2f(getPos().x + getSpeed().x, getPos().y + getSpeed().y));  //���������� ��������
		}
	}
	else {
		setPos(ofVec2f(posPlayer.x + sizePlayer.x / 2, posPlayer.y - getRadius()));   //���� ����� �� ����� �� ������������ �� �������
	}
}

Rect::Rect(ofVec2f pos, ofVec2f speed, ofVec2f size, bool player) : Figure(pos, speed)
{
	m_size = size;
	m_player = player;  //��������
}

void Rect::draw() const
{
	ofFill();
	ofSetColor(50, 50, 50);
	ofRect(getPos().x, getPos().y, getSize().x, getSize().y);  //���������
}

void Rect::setup()
{

}

void Rect::update(ofVec2f ballpos, int radius)
{

	if (!isPlayer()) {    //���� �� �����, ��������� �� �������(�������� ����� ��������������)
		if (getPos().x + getSize().x / 2 <= ballpos.x) {
			setSpeed(ofVec2f(4, 0));
		}
		else {
			setSpeed(ofVec2f(-4, 0));
		}
	}
	if (getPos().x < 0 && getSpeed().x < 0 || getPos().x + getSize().x > ofGetWidth() && getSpeed().x > 0) {  //�� ������� ���� ������� �� �����
		setSpeed(ofVec2f(0, 0));
	}
	setPos(ofVec2f(getPos().x + getSpeed().x, getPos().y + getSpeed().y));  //��������� ���������
}

void Rect::keyLeft()
{
	if (getPos().x < 0) {
		setSpeed(ofVec2f(0, 0));   //����������
	}
	else {
		setSpeed(ofVec2f(-5, 0));
	}
}

void Rect::keyRight()
{
	if (getPos().x + getSize().x > ofGetWidth()) { //����������
		setSpeed(ofVec2f(0, 0));
	}
	else {
		setSpeed(ofVec2f(5, 0));
	}
}
