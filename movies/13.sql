SELECT DISTINCT name
FROM ((people
INNER JOIN stars on people.id = stars.person_id)
INNER JOIN movies on movies.id = stars.movie_id)
WHERE people.name != "Kevin Bacon" AND title IN (

    SELECT title
    FROM ((movies
    INNER JOIN stars ON movies.id = stars.movie_id)
    INNER JOIN people ON people.id = stars.person_id)
    WHERE people.id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)
)
;