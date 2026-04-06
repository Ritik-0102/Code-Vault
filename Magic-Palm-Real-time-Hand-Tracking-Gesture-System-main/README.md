# 🪄 Magic Palm – Real-time Hand Tracking Gesture System

Magic Palm is an AI powered hand tracking project that detects palm movements & gestures in real-time using OpenCV + MediaPipe. It allows gesture based interaction and VFX effects using hand landmarks.

---

## 🚀 Features
- Live hand detection from webcam
- Real-time palm gesture tracking
- Uses Computer Vision based landmark detection
- Easy to modify for VFX overlays / gesture control
- Lightweight + Fast inference

---

## 🧠 Tech Stack
| Component | Used For |
|----------|----------|
| Python | Main Programming Language |
| OpenCV | Video frame input + processing |
| MediaPipe | Hand landmark detection (21 keypoints) |
| cvzone | Wrapper for easy gesture handling |

---

## 📁 Project Structure
Magic Palm/
│ action.py
│ effect.mp4
│ requirements.txt
│ README.md
│ details.pdf


---

## ▶️ Run Locally

```bash
pip install -r requirements.txt
python action.py

Make sure your webcam is connected
Press Q to quit the execution
