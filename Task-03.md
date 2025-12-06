# Task‑03: Image Captioning Project

##  Overview
This project implements an image captioning pipeline as part of internship Task‑03.  
The goal is to generate descriptive captions for images using deep learning techniques.

---

##  Steps Completed

### 1. Dataset Preparation
- Cleaned and tokenized captions.  
- Built vocabulary and padded sequences.  
- Created mapping between images and their captions.  

### 2. Feature Extraction
- Used ResNet50 to extract image features.  
- Saved features into `features.pkl` for reuse.  

### 3. Model Building
- Implemented an encoder–decoder architecture:  
  - **Encoder**: ResNet50 image features.  
  - **Decoder**: LSTM network for sequence generation.  
- Defined maximum caption length and tokenizer.  

### 4. Training
- Trained the model on prepared sequences.  
- Monitored loss across epochs.  
- Saved trained model in native Keras format (`caption_model.keras`).  

### 5. Inference
- Implemented caption generation functions:  
  - Greedy decoding.  
  - Beam search decoding.  
- Generated sample captions for test images.  

### 6. Evaluation
- Evaluated captions using BLEU scores.  
- Sample results:  
  - BLEU‑1: ~0.38  
  - BLEU‑2: ~0.19  
  - BLEU‑3: ~0.11  
  - BLEU‑4: ~0.02  

### 7. Artifacts
- `caption_model.keras` – trained model.  
- `tokenizer.pkl` – saved tokenizer.  
- `features.pkl` – extracted image features.  

---

## Sample Output
- Example generated caption: `"a a a dog"`  
- BLEU scores demonstrate pipeline functionality.  

---

##  Future Improvements
- Train on full Flickr8k dataset (8,000 images, 40k captions).  
- Increase epochs for better performance.  
- Apply smoothing in BLEU evaluation.  
- Experiment with larger beam sizes and sampling decoding.  

---

##  How to Use
1. Run `dataset_prep.py` to clean captions.  
2. Run `feature_extract.py` to generate `features.pkl`.  
3. Train the model with `main.py`.  
4. Use `beam_search_caption` for inference.  
5. Evaluate with BLEU scores.  
