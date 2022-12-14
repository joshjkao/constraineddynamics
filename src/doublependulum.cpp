#include "doublependulum.h"
#include <cmath>

LagrangianDoublePendulum::LagrangianDoublePendulum() {
    pivot = Vector2d(5, 1);
    updateVectors();
}

LagrangianDoublePendulum::~LagrangianDoublePendulum() {

}

void LagrangianDoublePendulum::setAngles(double t1, double t2) {
    theta1 = t1 * M_PI/180;
    theta2 = t2 * M_PI/180;
}

void LagrangianDoublePendulum::setMassRatio(double ratio) {
    m1 = ratio;
    m2 = 1;
}

void LagrangianDoublePendulum::clear() {
    theta1 = 0;
    theta1dot = 0;
    theta1ddot = 0;
    theta2 = 0;
    theta2dot = 0;
    theta2ddot = 0;
}

void LagrangianDoublePendulum::update() {
    theta1ddot=(-g*(2*m1+m2)*sin(theta1)-m2*g*sin(theta1-2*theta2)-2*sin(theta1-theta2)*m2*(r2*theta2dot*theta2dot+r1*cos(theta1-theta2)*theta1dot*theta1dot))/(r1*(2*m1+m2-m2*cos(2*theta1-2*theta2)));
    theta2ddot=(2*sin(theta1-theta2)*((m1+m2)*r1*theta1dot*theta1dot+g*(m1+m2)*cos(theta1)+r2*m2*cos(theta1-theta2)*theta2dot*theta2dot))/(r2*(2*m1+m2-m2*cos(2*theta1-2*theta2)));

    
    theta1 += dt * theta1dot;
    theta2 += dt * theta2dot;
    theta1dot += dt * theta1ddot;
    theta2dot += dt * theta2ddot;

    updateVectors();
}

void LagrangianDoublePendulum::render(SDL_Renderer* rend) {
    SDL_Rect rect;
    rect.x = string1.x*100-16*m1;
    rect.y = string1.y*100-16*m1;
    rect.w = 32*m1;
    rect.h = 32*m1;
    SDL_SetRenderDrawColor(rend, 150,150,150,255);
    SDL_RenderFillRect(rend, &rect);
    rect.x = string2.x*100-16*m2;
    rect.y = string2.y*100-16*m2;
    rect.w = 32*m2;
    rect.h = 32*m2;
    SDL_RenderFillRect(rend, &rect);
}

void LagrangianDoublePendulum::updateVectors() {
    string1.x = pivot.x + r1*sin(theta1);
    string1.y = pivot.y + r1*cos(theta1);
    string2.x = string1.x + r2*sin(theta2);
    string2.y = string1.y + r2*cos(theta2);
}

std::vector<double> LagrangianDoublePendulum::getState() {
    std::vector<double> result;

    result.push_back(m1);
    result.push_back(string1.x);
    result.push_back(r1 * cos(theta1) * theta1dot);
    result.push_back(string1.y);
    result.push_back(r1 * -1 * sin(theta1) * theta1dot);
    result.push_back(m2);
    result.push_back(string2.x);
    result.push_back(r1 * cos(theta1) * theta1dot + r2 * theta2dot * cos(theta2));
    result.push_back(string2.y);
    result.push_back(r1 * -1 * sin(theta1) * theta1dot - r2 * theta2dot * sin(theta2));

    return result;
}