# Task‑04: Movie Recommendation System

##  Overview
This task involves building a **Recommendation System** that suggests movies to users based on their preferences.  
The system uses **content‑based filtering** techniques, where movies are recommended by analyzing their genres and tags.

##  Objectives
- Implement a simple recommendation engine.
- Use **TF‑IDF vectorization** and **cosine similarity** to measure movie similarity.
- Provide recommendations for a given movie title.
- Document the process with clear steps and sample outputs.

##  Dataset
- **Source**: [MovieLens Latest Small Dataset](https://grouplens.org/datasets/movielens/latest/)  
- **Files Used**:
  - `movies.csv` → movieId, title, genres  
  - `tags.csv` → userId, movieId, tag, timestamp  
- Combined features: `genres + tags`

##  Approach
1. **Data Preparation**
   - Load `movies.csv` and `tags.csv` using Pandas.
   - Merge datasets on `movieId`.
   - Create a `combined_features` column (genres + tags).

2. **Feature Extraction**
   - Apply **TF‑IDF Vectorizer** to convert text features into numerical vectors.

3. **Similarity Computation**
   - Use **cosine similarity** (optimized with `linear_kernel`) to compute similarity scores between movies.

4. **Recommendation Function**
   - Input: Movie title.
   - Output: Top 5 similar movies based on similarity scores.

##  Code Snippet
```python
def recommend(title, df, similarity_matrix):
    index = df[df['title'] == title].index[0]
    scores = list(enumerate(similarity_matrix[index]))
    sorted_scores = sorted(scores, key=lambda x: x[1], reverse=True)
    recommended = [df['title'][i[0]] for i in sorted_scores[1:6]]
    return recommended

print(recommend("Toy Story (1995)", sample_df, similarity_matrix))
