# CardGame

A small card game prototype built with **Cocos2d-x** in C++.  
This project focuses on **clear code structure**, **basic card interaction**, **top-card update**, and **undo support**.

## Overview

This project implements a basic card-game prototype with the following features:

- Playfield card clicking
- Deck/hand top-card clicking
- Top-card update logic
- Basic card match rule
- Face-up / face-down state updates based on overlap
- Undo for the last operation
- Basic move animation

At the current stage, the game uses a **fixed test layout** instead of a full random shuffle/deal system.

---

## Project Structure

```text
Classes/
├── controllers/
│   └── GameController.h / GameController.cpp
├── models/
│   ├── CardModel.h / CardModel.cpp
│   ├── GameModel.h / GameModel.cpp
│   └── UndoModel.h / UndoModel.cpp
├── views/
│   ├── CardView.h / CardView.cpp
│   └── GameView.h / GameView.cpp
├── services/
│   └── CardMatchService.h / CardMatchService.cpp
├── managers/
│   └── UndoManager.h / UndoManager.cpp
├── HelloWorldScene.h / HelloWorldScene.cpp
└── AppDelegate.h / AppDelegate.cpp
