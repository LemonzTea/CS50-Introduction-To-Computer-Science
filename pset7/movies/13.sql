SELECT name FROM people
JOIN stars on people.id = stars.person_id
WHERE stars.movie_id IN(SELECT stars.movie_id FROM stars
                        JOIN people ON people.id = stars.person_id
                        WHERE people.name = "Kevin Bacon" and people.birth = "1958")
AND people.id NOT IN (SELECT id FROM people
                            WHERE people.name = "Kevin Bacon" and people.birth = "1958");



