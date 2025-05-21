from fastapi import FastAPI
from fastapi.responses import JSONResponse
from pydantic import BaseModel
from typing import Dict
import numpy as np
import pickle

from preprocess import preprocess

df = preprocess(my_data)


app = FastAPI()

# Load the model at startup
model = None

def load_model():
    global model
    try:
        with open("ebm_model.pkl", "rb") as f:
            model = pickle.load(f)
    except Exception as e:
        print("Error loading model:", e)
        model = None

load_model()

# Pydantic input model
class InputData(BaseModel):
    temp: float
    vibration: float
    current: float

# Root endpoint for welcome message
@app.get("/")
def read_root():
    return JSONResponse(content={"message": "Welcome to the Predictive Maintenance API!"})

# Predict endpoint
@app.post("/predict", response_model=Dict[str, int])
def predict(data: InputData):
    if model is None:
        return JSONResponse(status_code=503, content={"error": "Model not loaded"})

    try:
        input_data = data.dict()
        x = preprocess(input_data)  # Ensure this returns a 2D shape
        prediction = model.predict(x)
        return {"prediction": int(prediction[0])}
    except Exception as e:
        return JSONResponse(status_code=500, content={"error": str(e)})
