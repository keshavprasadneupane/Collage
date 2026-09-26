from fastapi import FastAPI
import uvicorn
from database import engine, Base
from fastapi.middleware.cors import CORSMiddleware  

# Create tables
Base.metadata.create_all(bind=engine)

app = FastAPI()

# --- CORS setup ---
origins = [
    "http://localhost:5500",  
    "http://127.0.0.1:5500",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,  # or ["*"] to allow all origins
    allow_credentials=True,
    allow_methods=["*"],  # allow GET, POST, etc.
    allow_headers=["*"],  # allow custom headers
)

# Include routers
from auth import auth as auth_router
from api import api as api_router

app.include_router(auth_router)
app.include_router(api_router)

@app.get("/")
async def root():
    return {"message": "FastAPI + SQLite is ready!"}

if __name__ == "__main__":
    uvicorn.run("main:app", host='0.0.0.0', port=8000, reload=True)