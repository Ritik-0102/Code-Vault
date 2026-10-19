# PostgreSQL Complete SQL Notes

## From beginner to LeetCode, interviews, and practical database work

**Goal:** Learn SQL using PostgreSQL, then solve SQL problems
confidently on LeetCode and other practice platforms.

These notes are a reference guide. Do not try to memorize every section
at once. Work through the fundamentals, type every query yourself in VS
Code, and solve problems topic by topic.

------------------------------------------------------------------------

## Contents

1.  How SQL and PostgreSQL fit together
2.  SQL statement categories
3.  Database, schema, table, row, and column
4.  PostgreSQL data types
5.  Creating databases and tables
6.  Constraints and keys
7.  Inserting, selecting, updating, and deleting data
8.  Filtering with `WHERE`
9.  Sorting, limiting, and pagination
10. NULL handling
11. Expressions, operators, and `CASE`
12. String functions
13. Numeric and mathematical functions
14. Date and time
15. Aggregate functions, `GROUP BY`, and `HAVING`
16. Joins
17. Subqueries and correlated subqueries
18. Set operations
19. CTEs and recursive CTEs
20. Window functions
21. Conditional aggregation and common SQL patterns
22. Data definition and schema changes
23. Transactions and concurrency basics
24. Views and materialized views
25. Indexes and query performance
26. Normalization and relationships
27. PostgreSQL-specific features
28. Query execution order
29. LeetCode SQL patterns and templates
30. Common mistakes and debugging
31. Practice plan and checklist
32. Quick reference sheet

------------------------------------------------------------------------

# 1. SQL and PostgreSQL

-   **SQL** is the language used to define, query, and manipulate
    relational data.
-   **PostgreSQL** is a relational database management system that
    executes SQL and provides additional features.
-   SQL is declarative: you usually specify *what result you want*, not
    the exact algorithm for finding it.
-   PostgreSQL follows SQL standards in many areas but also has its own
    syntax and features.

### Basic rules

1.  SQL keywords are conventionally written in uppercase, but SQL is
    generally case-insensitive for keywords.
2.  Unquoted identifiers such as `student_name` are folded to lowercase
    by PostgreSQL.
3.  Text literals use single quotes: `'Ritik'`.
4.  Double quotes are for identifiers: `"Order"`; avoid quoted
    identifiers unless necessary.
5.  End statements with semicolons, especially when running multiple
    statements.
6.  Use `--` for a single-line comment and `/* ... */` for a block
    comment.
7.  Prefer explicit column lists in `INSERT` statements.
8.  Never run an `UPDATE` or `DELETE` without checking whether the
    intended `WHERE` condition is present.
9.  SQL result rows have no guaranteed order unless `ORDER BY` is
    specified.
10. Use `IS NULL` and `IS NOT NULL`, not `= NULL`.

Example:

``` sql
-- Single-line comment
SELECT name, marks
FROM students
WHERE marks >= 80
ORDER BY marks DESC;
```

# 2. SQL statement categories

  -----------------------------------------------------------------------
  Category                Purpose                 Common statements
  ----------------------- ----------------------- -----------------------
  DDL                     Define or change        `CREATE`, `ALTER`,
                          structures              `DROP`, `TRUNCATE`

  DML                     Change data             `INSERT`, `UPDATE`,
                                                  `DELETE`, `MERGE`

  DQL (common teaching    Read data               `SELECT`
  term)                                           

  DCL                     Access permissions      `GRANT`, `REVOKE`

  TCL                     Transaction control     `BEGIN`, `COMMIT`,
                                                  `ROLLBACK`, `SAVEPOINT`
  -----------------------------------------------------------------------

`SELECT` can also be considered part of DML in some classifications; the
DQL category is a teaching convention.

# 3. Database objects

-   **Database:** a named collection of database objects.
-   **Schema:** a namespace inside a database, often used to organize
    tables and other objects. PostgreSQL's default schema is commonly
    `public`.
-   **Table:** data arranged in rows and columns.
-   **Row:** one record.
-   **Column:** one attribute of a record.
-   **View:** a stored query presented like a table.
-   **Index:** a data structure that can speed up particular searches or
    joins.
-   **Constraint:** a rule the database enforces.
-   **Sequence/identity:** a mechanism for generating numeric values.
-   **Function/procedure/trigger:** programmable database objects.

In PostgreSQL, connect to a database before creating ordinary tables. A
database connection is associated with one database at a time.

Useful inspection queries:

``` sql
SELECT current_database();
SELECT current_schema();
SELECT version();
SELECT CURRENT_USER;
```

# 4. PostgreSQL data types

Choose types based on the meaning and range of data.

## Numbers

-   `SMALLINT`: small integer.
-   `INTEGER` / `INT`: standard integer.
-   `BIGINT`: larger integer.
-   `NUMERIC(p, s)` / `DECIMAL(p, s)`: exact decimal values, useful for
    money-like quantities where exact arithmetic matters.
-   `REAL`, `DOUBLE PRECISION`: approximate floating-point values.
-   `SERIAL` / `BIGSERIAL`: older convenient sequence-backed integer
    patterns; identity columns are generally preferred for new designs.

Examples:

``` sql
age INTEGER,
price NUMERIC(10, 2),
rating DOUBLE PRECISION
```

## Text

-   `TEXT`: variable-length text without a declared length limit.
-   `VARCHAR(n)`: variable-length text with a maximum length.
-   `CHAR(n)`: fixed-width, blank-padded text; rarely needed for
    ordinary application fields.

For most PostgreSQL text columns, `TEXT` is a perfectly reasonable
choice. Use `VARCHAR(n)` when the maximum length is a meaningful rule.

## Boolean

``` sql
is_active BOOLEAN DEFAULT TRUE
```

Values are `TRUE`, `FALSE`, or `NULL` (unknown).

## Dates and times

-   `DATE`: calendar date.
-   `TIME`: time of day.
-   `TIMESTAMP`: date and time without a time-zone-aware instant.
-   `TIMESTAMPTZ`: timestamp with time-zone semantics; PostgreSQL stores
    an instant and displays it using the session time zone.
-   `INTERVAL`: duration.

For event timestamps representing real-world instants, `TIMESTAMPTZ` is
often appropriate.

## Other useful types

-   `UUID`: universally unique identifier.
-   `JSON` / `JSONB`: JSON data; `JSONB` is commonly preferred for
    querying/indexing JSON.
-   `BYTEA`: binary data.
-   Arrays, such as `INTEGER[]`.
-   Enumerated types (`CREATE TYPE ... AS ENUM`), useful when a fixed
    set of values is appropriate.
-   `INET`, `CIDR`, and geometric types for specialized use cases.

## Type conversion

``` sql
SELECT CAST('123' AS INTEGER);
SELECT '123'::INTEGER;              -- PostgreSQL shorthand
SELECT CAST(12.5 AS NUMERIC(5, 2));
```

Avoid relying on accidental implicit conversions. Make conversions
explicit when clarity matters.

# 5. Creating databases and tables

Create a database (run as a command outside a transaction block):

``` sql
CREATE DATABASE dbms_practice;
```

Create a table:

``` sql
CREATE TABLE students (
    student_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    age INTEGER CHECK (age >= 0),
    city TEXT,
    marks INTEGER CHECK (marks BETWEEN 0 AND 100),
    created_at TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
);
```

Add multiple rows:

``` sql
INSERT INTO students (student_id, name, age, city, marks)
VALUES
    (1, 'Ritik', 20, 'Jaipur', 85),
    (2, 'Aman', 21, 'Delhi', 76),
    (3, 'Priya', 19, 'Mumbai', 92);
```

The number and order of values must match the listed columns. If a
column has a default or allows `NULL`, it can be omitted.

Create a table from a query:

``` sql
CREATE TABLE high_scorers AS
SELECT student_id, name, marks
FROM students
WHERE marks >= 85;
```

This copies the query's result into a new table, but does not
automatically copy all constraints and indexes from the source.

Temporary table:

``` sql
CREATE TEMP TABLE temp_results (
    id INTEGER,
    result TEXT
);
```

Temporary tables are session-scoped by default.

# 6. Constraints and keys

Constraints protect data integrity.

## `PRIMARY KEY`

Uniquely identifies each row and does not allow `NULL`. A table has one
primary-key constraint, which may contain multiple columns.

``` sql
student_id INTEGER PRIMARY KEY
```

Composite key:

``` sql
PRIMARY KEY (student_id, course_id)
```

## `FOREIGN KEY`

Requires a value to match a referenced key (subject to the chosen
delete/update action).

``` sql
CREATE TABLE courses (
    course_id INTEGER PRIMARY KEY,
    course_name TEXT NOT NULL
);

CREATE TABLE enrollments (
    student_id INTEGER REFERENCES students(student_id),
    course_id INTEGER REFERENCES courses(course_id),
    enrolled_at DATE DEFAULT CURRENT_DATE,
    PRIMARY KEY (student_id, course_id)
);
```

Common referential actions include `ON DELETE CASCADE`,
`ON DELETE SET NULL`, `ON DELETE SET DEFAULT`, and `ON DELETE RESTRICT`
/ `NO ACTION`. Use cascading behavior deliberately.

## `UNIQUE`

Prevents duplicate non-null key values according to PostgreSQL's
uniqueness rules. By default, multiple `NULL` values are allowed in a
unique constraint; PostgreSQL also supports `NULLS NOT DISTINCT` in
supported versions.

``` sql
email TEXT UNIQUE
```

## `NOT NULL`

``` sql
name TEXT NOT NULL
```

## `CHECK`

``` sql
marks INTEGER CHECK (marks >= 0 AND marks <= 100)
```

A `CHECK` constraint passes when its expression is true or unknown;
combine it with `NOT NULL` when nulls must be prohibited.

## `DEFAULT`

``` sql
created_at TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
```

A default is used when a column is omitted or `DEFAULT` is specified,
not when an explicit `NULL` is inserted.

## Identity columns

``` sql
CREATE TABLE products (
    product_id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    product_name TEXT NOT NULL
);
```

`GENERATED BY DEFAULT AS IDENTITY` allows an explicit value to be
supplied more readily; `GENERATED ALWAYS` is stricter unless an override
is specified.

# 7. CRUD: INSERT, SELECT, UPDATE, DELETE

CRUD means Create, Read, Update, Delete.

## INSERT

``` sql
INSERT INTO students (student_id, name, age, city, marks)
VALUES (4, 'Neha', 20, 'Pune', 88);
```

Insert from another query:

``` sql
INSERT INTO high_scorers (student_id, name, marks)
SELECT student_id, name, marks
FROM students
WHERE marks >= 85;
```

Return inserted/changed rows:

``` sql
INSERT INTO students (student_id, name, age, marks)
VALUES (5, 'Karan', 19, 67)
RETURNING *;
```

## SELECT columns

``` sql
SELECT name, marks
FROM students;
```

All columns:

``` sql
SELECT *
FROM students;
```

For learning and production code, prefer listing columns instead of `*`
when the exact output matters.

Aliases:

``` sql
SELECT name AS student_name, marks AS score
FROM students AS s;
```

## UPDATE

``` sql
UPDATE students
SET marks = 90
WHERE student_id = 1
RETURNING *;
```

Update multiple columns:

``` sql
UPDATE students
SET city = 'Pune', marks = 91
WHERE student_id = 2;
```

Update using another table/query:

``` sql
UPDATE students AS s
SET marks = s.marks + 5
WHERE s.city = 'Delhi';
```

## DELETE

``` sql
DELETE FROM students
WHERE student_id = 5
RETURNING *;
```

Delete all rows (be careful):

``` sql
DELETE FROM students;
```

`DELETE` can use a `WHERE` clause and returns deleted rows with
`RETURNING`.

## UPSERT: `ON CONFLICT`

``` sql
INSERT INTO students (student_id, name, age, marks)
VALUES (1, 'Ritik', 20, 90)
ON CONFLICT (student_id)
DO UPDATE SET marks = EXCLUDED.marks
RETURNING *;
```

`EXCLUDED` refers to the proposed row that conflicted with an existing
unique/primary-key row.

Do not confuse this with MySQL's `ON DUPLICATE KEY UPDATE`; the syntax
differs.

# 8. Filtering with WHERE

Comparison operators:

-   `=` equal
-   `<>` or `!=` not equal
-   `>` greater than
-   `<` less than
-   `>=` greater than or equal
-   `<=` less than or equal

Examples:

``` sql
SELECT * FROM students WHERE marks >= 80;
SELECT * FROM students WHERE city <> 'Delhi';
SELECT * FROM students WHERE age = 20;
```

## Logical operators

``` sql
SELECT *
FROM students
WHERE marks >= 80 AND city = 'Jaipur';

SELECT *
FROM students
WHERE city = 'Delhi' OR city = 'Mumbai';

SELECT *
FROM students
WHERE NOT city = 'Delhi';
```

Use parentheses when mixing `AND` and `OR`:

``` sql
SELECT *
FROM students
WHERE city = 'Delhi'
  AND (marks >= 80 OR age < 20);
```

`AND` has higher precedence than `OR`. Parentheses make intent explicit.

## BETWEEN

Inclusive at both ends:

``` sql
SELECT *
FROM students
WHERE marks BETWEEN 70 AND 90;
```

Equivalent to `marks >= 70 AND marks <= 90`.

## IN / NOT IN

``` sql
SELECT *
FROM students
WHERE city IN ('Delhi', 'Jaipur');

SELECT *
FROM students
WHERE city NOT IN ('Delhi', 'Jaipur');
```

Caution: `NOT IN` can behave unexpectedly if its list/subquery contains
`NULL`. `NOT EXISTS` is often safer for anti-join logic.

## LIKE / ILIKE

`LIKE` is pattern matching; `ILIKE` is PostgreSQL's case-insensitive
form.

-   `%`: zero or more characters
-   `_`: exactly one character

``` sql
SELECT * FROM students WHERE name LIKE 'R%';       -- starts with R
SELECT * FROM students WHERE name LIKE '%a';       -- ends with a
SELECT * FROM students WHERE name LIKE '%it%';     -- contains it
SELECT * FROM students WHERE name ILIKE 'r%';      -- case-insensitive
SELECT * FROM students WHERE name LIKE '_a%';      -- second character is a
```

`LIKE` is not a regular expression. PostgreSQL also supports regex
operators such as `~` and case-insensitive `~*`.

## DISTINCT

``` sql
SELECT DISTINCT city
FROM students;

SELECT DISTINCT city, age
FROM students;
```

The second query returns unique *combinations* of city and age.

# 9. Sorting, LIMIT, OFFSET, and pagination

``` sql
SELECT *
FROM students
ORDER BY marks DESC, name ASC
LIMIT 10;
```

Multiple sort keys are applied left to right. If ties matter, add a
stable tie-breaker such as a primary key.

Pagination:

``` sql
SELECT *
FROM students
ORDER BY student_id
LIMIT 10 OFFSET 20;
```

This skips 20 rows and returns up to 10. Large offsets can be
inefficient. For large datasets, keyset pagination is often better:

``` sql
SELECT *
FROM students
WHERE student_id > 100
ORDER BY student_id
LIMIT 10;
```

`NULLS FIRST` and `NULLS LAST` control where nulls appear in sort order:

``` sql
SELECT *
FROM students
ORDER BY marks DESC NULLS LAST;
```

PostgreSQL defaults to nulls last for ascending order and nulls first
for descending order.

# 10. NULL handling

`NULL` means missing, unknown, or not applicable; it is not zero and is
not an empty string.

Incorrect:

``` sql
WHERE city = NULL
```

Correct:

``` sql
SELECT * FROM students WHERE city IS NULL;
SELECT * FROM students WHERE city IS NOT NULL;
```

## COALESCE

Returns the first non-null argument:

``` sql
SELECT name, COALESCE(city, 'Unknown') AS city
FROM students;
```

## NULLIF

Returns `NULL` if its two arguments are equal:

``` sql
SELECT total / NULLIF(count, 0)
FROM summary;
```

This avoids division by zero when `count = 0` (provided the resulting
expression's types are appropriate).

## Three-valued logic

Comparisons involving `NULL` usually produce `UNKNOWN`, not true or
false. `WHERE` keeps only rows where the condition is true.

For example:

``` sql
SELECT *
FROM students
WHERE marks <> 90;
```

Rows with `marks IS NULL` do not pass this condition. To include nulls:

``` sql
WHERE marks <> 90 OR marks IS NULL
```

## Null-safe comparison

PostgreSQL supports:

``` sql
a IS DISTINCT FROM b
a IS NOT DISTINCT FROM b
```

These treat nulls as comparable values and are useful for reliable
equality/inequality checks.

# 11. Expressions, operators, and CASE

Arithmetic operators include `+`, `-`, `*`, `/`, and `%` (remainder).
Integer division truncates fractional parts when both operands are
integers; cast to a decimal type if you need a fractional result.

``` sql
SELECT 5 / 2;                 -- integer result
SELECT 5::NUMERIC / 2;        -- decimal result
SELECT marks + 5 AS adjusted_marks
FROM students;
```

Concatenate strings with `||`:

``` sql
SELECT name || ' - ' || city AS student_info
FROM students;
```

## CASE

SQL's conditional expression:

``` sql
SELECT name, marks,
       CASE
           WHEN marks >= 90 THEN 'Excellent'
           WHEN marks >= 75 THEN 'Good'
           WHEN marks >= 60 THEN 'Average'
           ELSE 'Needs improvement'
       END AS grade
FROM students;
```

Simple CASE:

``` sql
SELECT name,
       CASE city
           WHEN 'Delhi' THEN 'North'
           WHEN 'Mumbai' THEN 'West'
           ELSE 'Other'
       END AS region
FROM students;
```

`CASE` is an expression, so it can appear in `SELECT`, `ORDER BY`,
aggregates, and many other contexts.

# 12. String functions

Frequently used PostgreSQL string functions:

``` sql
SELECT LENGTH('PostgreSQL');               -- character length
SELECT LOWER('HELLO'), UPPER('hello');
SELECT TRIM('  hello  ');
SELECT LTRIM('  hello'), RTRIM('hello  ');
SELECT SUBSTRING('PostgreSQL' FROM 1 FOR 4);
SELECT LEFT('PostgreSQL', 4), RIGHT('PostgreSQL', 3);
SELECT REPLACE('banana', 'a', 'o');
SELECT POSITION('SQL' IN 'PostgreSQL');
SELECT CONCAT('Hello', ' ', 'World');
SELECT 'Hello' || ' ' || 'World';
SELECT SPLIT_PART('a,b,c', ',', 2);         -- b
SELECT REPEAT('ha', 3);
SELECT REVERSE('abc');
```

Padding:

``` sql
SELECT LPAD('42', 5, '0');                  -- 00042
SELECT RPAD('SQL', 5, '.');                 -- SQL..
```

Regex replacement:

``` sql
SELECT REGEXP_REPLACE('a12b34', '[0-9]+', '#', 'g');
```

The `g` flag replaces all matches. Be aware of case sensitivity and
whether a function counts characters or bytes.

# 13. Numeric and mathematical functions

``` sql
SELECT ABS(-10);
SELECT ROUND(12.345, 2);
SELECT CEIL(4.2);
SELECT FLOOR(4.8);
SELECT POWER(2, 3);
SELECT SQRT(25);
SELECT MOD(10, 3);
SELECT GREATEST(2, 9, 4);
SELECT LEAST(2, 9, 4);
```

Random values:

``` sql
SELECT RANDOM();  -- approximate value in [0, 1)
```

For division and averages, consider type behavior and zero denominators.

# 14. Dates and times

Useful current values:

``` sql
SELECT CURRENT_DATE;
SELECT CURRENT_TIME;
SELECT CURRENT_TIMESTAMP;
SELECT NOW();
```

Date arithmetic:

``` sql
SELECT CURRENT_DATE + 7;                         -- seven days later
SELECT CURRENT_DATE - DATE '2026-01-01';         -- integer number of days
SELECT NOW() + INTERVAL '3 days';
SELECT NOW() - INTERVAL '2 hours';
```

Extract parts:

``` sql
SELECT EXTRACT(YEAR FROM DATE '2026-10-16');
SELECT EXTRACT(MONTH FROM CURRENT_DATE);
SELECT EXTRACT(DOW FROM CURRENT_DATE);           -- Sunday=0
SELECT DATE_TRUNC('month', CURRENT_TIMESTAMP);
```

Formatting:

``` sql
SELECT TO_CHAR(CURRENT_DATE, 'YYYY-MM-DD');
SELECT TO_CHAR(CURRENT_TIMESTAMP, 'DD Mon YYYY HH24:MI');
```

Parsing:

``` sql
SELECT TO_DATE('16-10-2026', 'DD-MM-YYYY');
SELECT TO_TIMESTAMP('2026-10-16 14:30', 'YYYY-MM-DD HH24:MI');
```

Date filters should often use half-open ranges for timestamps:

``` sql
WHERE created_at >= TIMESTAMP '2026-10-01 00:00:00'
  AND created_at <  TIMESTAMP '2026-11-01 00:00:00'
```

This avoids missing fractional seconds at the end of a day/month. For
`TIMESTAMPTZ`, use time-zone-aware boundaries when the intended time
zone matters.

# 15. Aggregate functions, GROUP BY, HAVING

Aggregates summarize multiple rows.

-   `COUNT(*)`: counts rows.
-   `COUNT(column)`: counts non-null values in that column.
-   `COUNT(DISTINCT column)`: counts distinct non-null values.
-   `SUM(column)`: sum of non-null values.
-   `AVG(column)`: average of non-null values.
-   `MIN(column)`, `MAX(column)`: minimum and maximum.
-   `STRING_AGG(value, delimiter)`: concatenate values across rows.
-   `ARRAY_AGG(value)`: collect values into an array.

Examples:

``` sql
SELECT COUNT(*) FROM students;
SELECT AVG(marks) FROM students;
SELECT MIN(marks), MAX(marks), SUM(marks) FROM students;
SELECT COUNT(DISTINCT city) FROM students;
```

## GROUP BY

One output row per group:

``` sql
SELECT city, COUNT(*) AS student_count
FROM students
GROUP BY city;
```

Average marks by city:

``` sql
SELECT city, AVG(marks) AS average_marks
FROM students
GROUP BY city;
```

Any selected column that is not aggregated generally needs to be
included in `GROUP BY`, subject to PostgreSQL's functional-dependency
rules.

## HAVING

Filters groups after aggregation:

``` sql
SELECT city, COUNT(*) AS student_count
FROM students
GROUP BY city
HAVING COUNT(*) >= 2;
```

Difference:

-   `WHERE` filters input rows before grouping.
-   `HAVING` filters groups after grouping.

Combine them:

``` sql
SELECT city, AVG(marks) AS avg_marks
FROM students
WHERE marks IS NOT NULL
GROUP BY city
HAVING AVG(marks) >= 80;
```

## Conditional aggregation

``` sql
SELECT
    COUNT(*) AS total_students,
    COUNT(*) FILTER (WHERE marks >= 80) AS high_scorers,
    AVG(marks) FILTER (WHERE city = 'Delhi') AS delhi_average
FROM students;
```

Equivalent style using `CASE`:

``` sql
SELECT
    SUM(CASE WHEN marks >= 80 THEN 1 ELSE 0 END) AS high_scorers
FROM students;
```

PostgreSQL's aggregate `FILTER` clause is particularly convenient.

## Ordered aggregates

``` sql
SELECT city,
       STRING_AGG(name, ', ' ORDER BY name) AS students
FROM students
GROUP BY city;
```

The order inside `STRING_AGG` determines concatenation order.

# 16. Joins

Assume these tables:

``` sql
CREATE TABLE departments (
    department_id INTEGER PRIMARY KEY,
    department_name TEXT NOT NULL
);

CREATE TABLE employees (
    employee_id INTEGER PRIMARY KEY,
    employee_name TEXT NOT NULL,
    department_id INTEGER REFERENCES departments(department_id),
    salary NUMERIC(10, 2)
);
```

## INNER JOIN

Only matching rows:

``` sql
SELECT e.employee_name, d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id;
```

`JOIN` by itself means `INNER JOIN`.

## LEFT JOIN

All left-table rows, with matching right-side data where available;
unmatched right-side columns become `NULL`.

``` sql
SELECT e.employee_name, d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id;
```

Find employees without a matching department:

``` sql
SELECT e.*
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.department_id IS NULL;
```

## RIGHT JOIN

Keeps all rows from the right table. It is often possible to rewrite a
right join as a left join by reversing table order.

## FULL OUTER JOIN

Keeps matched rows and unmatched rows from both sides:

``` sql
SELECT e.employee_name, d.department_name
FROM employees AS e
FULL OUTER JOIN departments AS d
    ON e.department_id = d.department_id;
```

## CROSS JOIN

Returns every combination of rows from both tables:

``` sql
SELECT *
FROM employees
CROSS JOIN departments;
```

If one table has 3 rows and the other has 4, the result has 12 rows.

## SELF JOIN

Join a table to itself, such as employees and their managers:

``` sql
SELECT e.employee_name AS employee,
       m.employee_name AS manager
FROM employees AS e
LEFT JOIN employees AS m
    ON e.manager_id = m.employee_id;
```

This example requires a `manager_id` column in `employees`.

## Join conditions versus filters

Be careful when filtering the right table of a left join.

This can effectively remove unmatched rows:

``` sql
SELECT *
FROM employees e
LEFT JOIN departments d ON e.department_id = d.department_id
WHERE d.department_name = 'Engineering';
```

If you want to preserve every employee and match only Engineering
departments, put the condition in `ON`:

``` sql
SELECT *
FROM employees e
LEFT JOIN departments d
  ON e.department_id = d.department_id
 AND d.department_name = 'Engineering';
```

## Joining more than two tables

``` sql
SELECT s.name, c.course_name, e.enrolled_at
FROM students s
JOIN enrollments e ON e.student_id = s.student_id
JOIN courses c ON c.course_id = e.course_id;
```

Know the relationship cardinality: one-to-one, one-to-many, and
many-to-many. A many-to-many relationship is commonly represented by a
junction table such as `enrollments`.

# 17. Subqueries

A subquery is a query nested inside another query.

## Scalar subquery

Returns one value:

``` sql
SELECT name, marks
FROM students
WHERE marks > (SELECT AVG(marks) FROM students);
```

The inner query computes the average; the outer query selects students
above it.

## `IN` with a subquery

``` sql
SELECT name
FROM students
WHERE student_id IN (
    SELECT student_id
    FROM enrollments
    WHERE course_id = 10
);
```

## `EXISTS`

Checks whether at least one matching row exists:

``` sql
SELECT s.name
FROM students s
WHERE EXISTS (
    SELECT 1
    FROM enrollments e
    WHERE e.student_id = s.student_id
);
```

`SELECT 1` is conventional because only existence matters, not the
selected value.

## `NOT EXISTS`

Find students with no enrollment:

``` sql
SELECT s.name
FROM students s
WHERE NOT EXISTS (
    SELECT 1
    FROM enrollments e
    WHERE e.student_id = s.student_id
);
```

This is a robust anti-join pattern and avoids the `NULL` trap associated
with `NOT IN`.

## Correlated subquery

A subquery that references a row from the outer query:

``` sql
SELECT e.employee_name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department_id = e.department_id
);
```

This returns employees paid above their own department's average.

## ANY and ALL

``` sql
WHERE salary > ANY (SELECT salary FROM employees WHERE department_id = 2)
WHERE salary > ALL (SELECT salary FROM employees WHERE department_id = 2)
```

-   `> ANY`: greater than at least one value.
-   `> ALL`: greater than every value.
-   Empty-set and `NULL` behavior matters; test edge cases.

## Subquery in FROM

``` sql
SELECT city, avg_marks
FROM (
    SELECT city, AVG(marks) AS avg_marks
    FROM students
    GROUP BY city
) AS city_summary
WHERE avg_marks >= 80;
```

A derived table in `FROM` needs an alias in PostgreSQL.

# 18. Set operations

Set operations combine compatible query results. Each query should
return the same number of columns with compatible types.

## UNION

Combines results and removes duplicates:

``` sql
SELECT city FROM students
UNION
SELECT city FROM employees;
```

## UNION ALL

Keeps duplicates and is often faster:

``` sql
SELECT city FROM students
UNION ALL
SELECT city FROM employees;
```

## INTERSECT

Returns rows present in both results:

``` sql
SELECT city FROM students
INTERSECT
SELECT city FROM employees;
```

## EXCEPT

Returns rows from the first result that do not appear in the second:

``` sql
SELECT city FROM students
EXCEPT
SELECT city FROM employees;
```

The final `ORDER BY` normally belongs at the end of the compound query.
Parenthesize component queries when their individual limits/orderings
are needed.

# 19. CTEs and recursive CTEs

CTE stands for Common Table Expression. It is introduced with `WITH` and
gives a subquery a name.

``` sql
WITH high_scorers AS (
    SELECT student_id, name, marks
    FROM students
    WHERE marks >= 85
)
SELECT *
FROM high_scorers
ORDER BY marks DESC;
```

Multiple CTEs:

``` sql
WITH city_averages AS (
    SELECT city, AVG(marks) AS avg_marks
    FROM students
    GROUP BY city
),
above_average_cities AS (
    SELECT city, avg_marks
    FROM city_averages
    WHERE avg_marks >= 80
)
SELECT *
FROM above_average_cities;
```

CTEs improve readability, especially for multi-step problems. They are
not automatically faster than subqueries; PostgreSQL may inline or
materialize CTEs depending on the query and hints.

## Recursive CTE

Useful for hierarchical data such as employee reporting structures,
category trees, and graph traversal.

``` sql
WITH RECURSIVE numbers(n) AS (
    SELECT 1
    UNION ALL
    SELECT n + 1
    FROM numbers
    WHERE n < 5
)
SELECT n
FROM numbers;
```

Result: 1 through 5.

Recursive structure: 1. Anchor query: starting rows. 2. `UNION ALL`. 3.
Recursive query: references the CTE and generates the next rows. 4. Stop
when the recursive query produces no more rows or the condition stops
expansion.

For graphs/hierarchies, protect against cycles and unbounded recursion.

# 20. Window functions

Window functions calculate values across a related set of rows **without
collapsing the rows into one row per group**.

General syntax:

``` sql
function_name(...) OVER (
    PARTITION BY ...
    ORDER BY ...
    ROWS BETWEEN ... AND ...
)
```

## `ROW_NUMBER`, `RANK`, `DENSE_RANK`

``` sql
SELECT name, city, marks,
       ROW_NUMBER() OVER (PARTITION BY city ORDER BY marks DESC) AS row_num,
       RANK()       OVER (PARTITION BY city ORDER BY marks DESC) AS rank_num,
       DENSE_RANK() OVER (PARTITION BY city ORDER BY marks DESC) AS dense_rank_num
FROM students;
```

-   `ROW_NUMBER`: unique sequential number even for ties.
-   `RANK`: ties share a rank; gaps follow (1, 1, 3).
-   `DENSE_RANK`: ties share a rank; no gaps (1, 1, 2).

Add a tie-breaker to `ROW_NUMBER` if deterministic ordering is needed,
e.g. `ORDER BY marks DESC, student_id`.

## Top N per group

``` sql
WITH ranked AS (
    SELECT s.*,
           ROW_NUMBER() OVER (
               PARTITION BY city
               ORDER BY marks DESC, student_id
           ) AS rn
    FROM students s
)
SELECT *
FROM ranked
WHERE rn <= 2;
```

Use `RANK` or `DENSE_RANK` instead if ties should cause more than N rows
to be returned.

## `LAG` and `LEAD`

Access a previous or following row in the window order:

``` sql
SELECT name, marks,
       LAG(marks) OVER (ORDER BY student_id) AS previous_marks,
       LEAD(marks) OVER (ORDER BY student_id) AS next_marks
FROM students;
```

Can compare current and previous values, detect changes, and calculate
period-over-period differences.

## Running totals and moving averages

``` sql
SELECT student_id, marks,
       SUM(marks) OVER (
           ORDER BY student_id
           ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
       ) AS running_total
FROM students;
```

Moving average over the current and previous two rows:

``` sql
SELECT student_id, marks,
       AVG(marks) OVER (
           ORDER BY student_id
           ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
       ) AS moving_avg
FROM students;
```

## `FIRST_VALUE`, `LAST_VALUE`, `NTH_VALUE`

These depend on window ordering and frame definitions. `LAST_VALUE` can
surprise beginners because the default frame often ends at the current
row/peer group, not necessarily the end of the entire partition. To get
the final value for a partition:

``` sql
LAST_VALUE(marks) OVER (
    PARTITION BY city
    ORDER BY marks
    ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
)
```

## Window frame basics

-   `PARTITION BY`: split rows into independent groups.
-   `ORDER BY`: determine row order within each partition.
-   `ROWS`: frame based on physical row positions.
-   `RANGE` / `GROUPS`: frame semantics based on ordering values or peer
    groups.

When a running aggregate should advance one row at a time, explicitly
using `ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW` is often clear
and avoids peer-group surprises.

Window functions are commonly computed after `WHERE` and `GROUP BY`, so
filtering on a window result usually requires a subquery or CTE.

# 21. Conditional aggregation and common patterns

## Count rows matching a condition

``` sql
SELECT
    COUNT(*) AS total,
    COUNT(*) FILTER (WHERE marks >= 80) AS passed_threshold
FROM students;
```

Portable-style alternative:

``` sql
SELECT SUM(CASE WHEN marks >= 80 THEN 1 ELSE 0 END) AS passed_threshold
FROM students;
```

## Percentage

``` sql
SELECT
    100.0 * COUNT(*) FILTER (WHERE marks >= 40)
    / NULLIF(COUNT(*), 0) AS pass_percentage
FROM students;
```

Use `100.0` or cast to a decimal type to avoid integer division.
`NULLIF` protects against division by zero.

## Find duplicates

``` sql
SELECT email, COUNT(*) AS occurrences
FROM users
GROUP BY email
HAVING COUNT(*) > 1;
```

If nulls should not be included, add `WHERE email IS NOT NULL`.

## Rows whose value equals the maximum

``` sql
SELECT *
FROM employees
WHERE salary = (SELECT MAX(salary) FROM employees);
```

This returns all tied highest-paid employees.

## Second-highest distinct value

``` sql
SELECT MAX(salary) AS second_highest_salary
FROM employees
WHERE salary < (SELECT MAX(salary) FROM employees);
```

If there is no second distinct salary, the result is `NULL`.

Alternative using ranking:

``` sql
WITH ranked AS (
    SELECT salary,
           DENSE_RANK() OVER (ORDER BY salary DESC) AS rnk
    FROM employees
)
SELECT DISTINCT salary
FROM ranked
WHERE rnk = 2;
```

## Employees earning above their department average

``` sql
SELECT e.*
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department_id = e.department_id
);
```

## Find entities with no related rows

``` sql
SELECT c.*
FROM customers c
WHERE NOT EXISTS (
    SELECT 1
    FROM orders o
    WHERE o.customer_id = c.customer_id
);
```

## Latest row per group

``` sql
WITH ranked AS (
    SELECT o.*,
           ROW_NUMBER() OVER (
               PARTITION BY customer_id
               ORDER BY order_date DESC, order_id DESC
           ) AS rn
    FROM orders o
)
SELECT *
FROM ranked
WHERE rn = 1;
```

## Consecutive dates / gaps and islands

Common techniques include `LAG` to compare a row with its predecessor,
row-number differences for consecutive sequences, and recursive CTEs for
more complicated traversals. Always define what counts as consecutive
and how duplicates/nulls should behave.

# 22. ALTER, DROP, TRUNCATE, and schema changes

Add a column:

``` sql
ALTER TABLE students
ADD COLUMN email TEXT;
```

Change a type:

``` sql
ALTER TABLE students
ALTER COLUMN marks TYPE NUMERIC(5, 2);
```

Set/drop a default:

``` sql
ALTER TABLE students
ALTER COLUMN marks SET DEFAULT 0;

ALTER TABLE students
ALTER COLUMN marks DROP DEFAULT;
```

Set a column not null (existing rows must satisfy the rule):

``` sql
ALTER TABLE students
ALTER COLUMN name SET NOT NULL;
```

Add a named constraint:

``` sql
ALTER TABLE students
ADD CONSTRAINT marks_range CHECK (marks BETWEEN 0 AND 100);
```

Rename a column/table:

``` sql
ALTER TABLE students RENAME COLUMN name TO student_name;
ALTER TABLE students RENAME TO learners;
```

Drop a column:

``` sql
ALTER TABLE students DROP COLUMN email;
```

Remove a table:

``` sql
DROP TABLE students;
```

Remove all rows:

``` sql
TRUNCATE TABLE students;
```

Differences: - `DELETE`: removes selected rows and supports `WHERE`. -
`TRUNCATE`: removes all rows efficiently; no `WHERE`. - `DROP`: removes
the table object itself.

`TRUNCATE` and `DROP` are destructive. Transactions can roll back many
such changes in PostgreSQL, but never rely on rollback as a substitute
for care.

# 23. Transactions and concurrency basics

A transaction groups statements into one logical unit.

``` sql
BEGIN;

UPDATE accounts
SET balance = balance - 100
WHERE account_id = 1;

UPDATE accounts
SET balance = balance + 100
WHERE account_id = 2;

COMMIT;
```

If something goes wrong before commit:

``` sql
ROLLBACK;
```

Savepoints:

``` sql
BEGIN;
UPDATE students SET marks = marks + 1 WHERE student_id = 1;
SAVEPOINT before_second_change;
UPDATE students SET marks = marks + 1 WHERE student_id = 2;
ROLLBACK TO SAVEPOINT before_second_change;
COMMIT;
```

ACID: - **Atomicity:** all-or-nothing transaction behavior. -
**Consistency:** constraints and rules remain satisfied. -
**Isolation:** concurrent transactions are controlled according to the
isolation level. - **Durability:** committed changes persist according
to the system's durability guarantees.

PostgreSQL isolation levels include Read Committed (default), Repeatable
Read, and Serializable, plus Read Uncommitted which behaves like Read
Committed in PostgreSQL. Learn locking, deadlocks, MVCC, and transaction
anomalies after core querying.

# 24. Views and materialized views

A view stores a query definition:

``` sql
CREATE VIEW high_scorers AS
SELECT student_id, name, marks
FROM students
WHERE marks >= 85;
```

Use it:

``` sql
SELECT * FROM high_scorers;
```

Replace/drop:

``` sql
CREATE OR REPLACE VIEW high_scorers AS
SELECT student_id, name, marks
FROM students
WHERE marks >= 90;

DROP VIEW high_scorers;
```

A materialized view stores the query result physically:

``` sql
CREATE MATERIALIZED VIEW city_stats AS
SELECT city, COUNT(*) AS student_count, AVG(marks) AS avg_marks
FROM students
GROUP BY city;
```

Refresh it after source data changes:

``` sql
REFRESH MATERIALIZED VIEW city_stats;
```

A materialized view can make repeated expensive reads faster but can
become stale until refreshed.

# 25. Indexes and performance

An index can help PostgreSQL find rows faster, but it costs disk space
and adds work to inserts/updates/deletes.

Basic B-tree index:

``` sql
CREATE INDEX idx_students_city ON students(city);
```

Composite index:

``` sql
CREATE INDEX idx_students_city_marks
ON students(city, marks DESC);
```

Column order matters. An index on `(city, marks)` is especially useful
for queries filtering by `city`, and can help with sorting/filtering by
`marks` within a city.

Unique index:

``` sql
CREATE UNIQUE INDEX idx_users_email_unique ON users(email);
```

Partial index:

``` sql
CREATE INDEX idx_active_users
ON users(created_at)
WHERE is_active = TRUE;
```

Expression index:

``` sql
CREATE INDEX idx_users_lower_email ON users(LOWER(email));
```

This can help queries using the same expression, such as
`WHERE LOWER(email) = LOWER('A@EXAMPLE.COM')`.

Inspect query plans:

``` sql
EXPLAIN
SELECT *
FROM students
WHERE city = 'Delhi';

EXPLAIN ANALYZE
SELECT *
FROM students
WHERE city = 'Delhi';
```

`EXPLAIN ANALYZE` actually runs the query. Be careful with expensive or
data-modifying statements. Learn to interpret sequential scans, index
scans, join algorithms, row estimates, actual rows, and execution time.

General advice: - Measure before optimizing. - Index columns used
frequently in selective filters, joins, and ordering, based on
workload. - Do not index every column. - Keep statistics current;
PostgreSQL uses `ANALYZE` and autovacuum. - Avoid applying a function to
an indexed column unless a matching expression index or other strategy
is used. - Select only the columns you need. - Use appropriate types and
constraints.

# 26. Normalization and relationships

Even when focusing on query problems, understand schema structure.

-   **1NF:** values are atomic for the intended model; avoid repeating
    groups in a single field.
-   **2NF:** in 1NF, and every non-key attribute depends on the whole
    candidate key, not just part of a composite key.
-   **3NF:** in 2NF, and non-key attributes do not have inappropriate
    transitive dependencies on candidate keys.
-   **BCNF:** every determinant is a candidate key (informally, each
    nontrivial functional dependency has a superkey on the left).

Normalization reduces duplication and update anomalies. Denormalization
can be useful for measured performance or reporting needs, but should be
intentional.

Common relationship patterns: - One-to-one: unique foreign key. -
One-to-many: foreign key on the many side. - Many-to-many: junction
table with two foreign keys, often a composite primary key.

# 27. PostgreSQL-specific features

## `RETURNING`

Return changed rows without a separate query:

``` sql
UPDATE students
SET marks = marks + 1
WHERE city = 'Delhi'
RETURNING student_id, name, marks;
```

## `ILIKE`

Case-insensitive pattern matching:

``` sql
SELECT * FROM students WHERE name ILIKE 'ri%';
```

## `DISTINCT ON`

PostgreSQL extension for one row per distinct key, commonly used for
latest-per-group queries:

``` sql
SELECT DISTINCT ON (customer_id) *
FROM orders
ORDER BY customer_id, order_date DESC, order_id DESC;
```

The `ORDER BY` should start with the `DISTINCT ON` expressions and then
specify which row to keep.

## `FILTER` on aggregates

``` sql
SELECT COUNT(*) FILTER (WHERE marks >= 80)
FROM students;
```

## `generate_series`

Generate a series of numbers or timestamps:

``` sql
SELECT generate_series(1, 10);

SELECT generate_series(
    DATE '2026-10-01',
    DATE '2026-10-07',
    INTERVAL '1 day'
);
```

## Arrays

``` sql
SELECT ARRAY[1, 2, 3];
SELECT 2 = ANY (ARRAY[1, 2, 3]);
```

Array operators and indexing are useful in some cases, but a normalized
relational design is usually preferable for core entity relationships.

## JSONB

``` sql
CREATE TABLE events (
    event_id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    payload JSONB NOT NULL
);

SELECT payload -> 'user' AS user_object,
       payload ->> 'event_type' AS event_type_text
FROM events;
```

-   `->` returns JSON/JSONB.
-   `->>` returns text.
-   JSONB supports indexing strategies such as GIN indexes.

## Upsert

`INSERT ... ON CONFLICT ... DO UPDATE` is PostgreSQL's common upsert
syntax (covered earlier).

## `LATERAL`

Allows a `FROM` subquery to reference preceding `FROM` items. It is
useful for top-N-per-parent and correlated table expressions:

``` sql
SELECT c.customer_id, recent.order_id, recent.order_date
FROM customers c
LEFT JOIN LATERAL (
    SELECT o.order_id, o.order_date
    FROM orders o
    WHERE o.customer_id = c.customer_id
    ORDER BY o.order_date DESC
    LIMIT 1
) AS recent ON TRUE;
```

## Full-text search

PostgreSQL has `tsvector`, `tsquery`, and matching operators such as
`@@`; this is an advanced topic after ordinary `LIKE` and indexing.

## Functions, procedures, and triggers

These are useful for database-side logic, but LeetCode SQL generally
focuses on queries rather than writing PL/pgSQL. Learn them after joins,
subqueries, CTEs, and windows.

# 28. Logical query processing order

A useful mental model for a `SELECT` query is:

1.  `FROM` and joins
2.  `WHERE`
3.  `GROUP BY`
4.  `HAVING`
5.  `SELECT` expressions
6.  `DISTINCT`
7.  `ORDER BY`
8.  `LIMIT` / `OFFSET`

This is a logical model, not a guarantee of the physical execution plan.

It explains several common errors: - A `SELECT` alias usually cannot be
referenced in `WHERE`, because `WHERE` is logically evaluated earlier. -
`WHERE` cannot directly filter an aggregate such as `COUNT(*)`; use
`HAVING` or a subquery. - Window results are commonly filtered in an
outer query/CTE. - A final `ORDER BY` is required for guaranteed output
order.

Example:

``` sql
SELECT city, AVG(marks) AS avg_marks
FROM students
WHERE marks IS NOT NULL
GROUP BY city
HAVING AVG(marks) > 75
ORDER BY avg_marks DESC
LIMIT 5;
```

# 29. LeetCode SQL patterns and templates

LeetCode schemas vary by problem. Read the table definitions and exact
expected output carefully. Usually, write only the requested query, not
`CREATE TABLE` or sample inserts. Use the SQL dialect selected by the
platform; PostgreSQL and MySQL syntax are not identical.

## Pattern A: Simple filter

``` sql
SELECT column1, column2
FROM table_name
WHERE condition;
```

## Pattern B: Sort and top N

``` sql
SELECT *
FROM table_name
ORDER BY score DESC, id ASC
LIMIT 3;
```

## Pattern C: Group and filter groups

``` sql
SELECT category, COUNT(*) AS total
FROM items
GROUP BY category
HAVING COUNT(*) >= 2;
```

## Pattern D: Join two tables

``` sql
SELECT a.id, b.value
FROM table_a a
JOIN table_b b ON b.a_id = a.id;
```

## Pattern E: Keep all left rows

``` sql
SELECT a.id, b.value
FROM table_a a
LEFT JOIN table_b b ON b.a_id = a.id;
```

## Pattern F: Find rows with no match

``` sql
SELECT a.*
FROM table_a a
WHERE NOT EXISTS (
    SELECT 1
    FROM table_b b
    WHERE b.a_id = a.id
);
```

## Pattern G: Compare to average

``` sql
SELECT *
FROM employees
WHERE salary > (SELECT AVG(salary) FROM employees);
```

## Pattern H: Rank within groups

``` sql
WITH ranked AS (
    SELECT t.*,
           DENSE_RANK() OVER (
               PARTITION BY group_id
               ORDER BY score DESC
           ) AS rnk
    FROM table_name t
)
SELECT *
FROM ranked
WHERE rnk <= 3;
```

## Pattern I: Latest record per entity

``` sql
WITH ranked AS (
    SELECT t.*,
           ROW_NUMBER() OVER (
               PARTITION BY entity_id
               ORDER BY created_at DESC, id DESC
           ) AS rn
    FROM table_name t
)
SELECT *
FROM ranked
WHERE rn = 1;
```

## Pattern J: Conditional count

``` sql
SELECT group_id,
       COUNT(*) FILTER (WHERE status = 'active') AS active_count
FROM table_name
GROUP BY group_id;
```

## Pattern K: Consecutive values / previous row

``` sql
WITH x AS (
    SELECT *,
           LAG(value) OVER (ORDER BY event_time) AS previous_value
    FROM measurements
)
SELECT *
FROM x
WHERE value > previous_value;
```

## Pattern L: Duplicate values

``` sql
SELECT email
FROM users
GROUP BY email
HAVING COUNT(*) > 1;
```

## Pattern M: Median / percentile

PostgreSQL supports ordered-set aggregates such as:

``` sql
SELECT percentile_cont(0.5) WITHIN GROUP (ORDER BY salary)
FROM employees;
```

`percentile_cont` may interpolate; `percentile_disc` returns an observed
value.

## Pattern N: Running sum

``` sql
SELECT account_id, event_time, amount,
       SUM(amount) OVER (
           PARTITION BY account_id
           ORDER BY event_time, transaction_id
           ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
       ) AS running_balance_change
FROM transactions;
```

Use a deterministic ordering when multiple rows share a timestamp.

## Pattern O: Pivot-like output with conditional aggregation

``` sql
SELECT department_id,
       COUNT(*) FILTER (WHERE gender = 'F') AS female_count,
       COUNT(*) FILTER (WHERE gender = 'M') AS male_count
FROM employees
GROUP BY department_id;
```

## Pattern P: Percentage of total

``` sql
SELECT category,
       COUNT(*) AS category_count,
       100.0 * COUNT(*) / SUM(COUNT(*)) OVER () AS pct_of_total
FROM products
GROUP BY category;
```

## LeetCode-specific habits

-   Read whether the expected output includes duplicates.
-   Handle ties exactly as requested.
-   Determine whether missing values should be included.
-   Check whether the task asks for the second **row** or second
    **distinct value**.
-   A left join can produce `NULL` for missing related records; use
    `COALESCE` only if the expected output requires a replacement.
-   Don't add `ORDER BY` unless required or needed to define a
    window/top-N result; platforms usually compare result sets according
    to their own rules.
-   Use aliases exactly as requested when the expected column names
    matter.
-   For "at least one" use `EXISTS` or `ANY` as appropriate; for "none"
    use `NOT EXISTS`.
-   Test duplicates and edge cases mentally: empty groups, all-null
    values, ties, no second-highest value, and missing relationships.

# 30. Common mistakes and debugging

1.  **Using `= NULL`:** use `IS NULL`.
2.  **Forgetting `WHERE` in `UPDATE`/`DELETE`:** preview affected rows
    with a `SELECT` first.
3.  **Using aggregate functions in `WHERE`:** use `HAVING` or a
    subquery.
4.  **Selecting ungrouped columns:** aggregate them or include them in
    the grouping logic.
5.  **Using `COUNT(column)` when you need row count:** use `COUNT(*)`.
6.  **Using `COUNT(*)` when you need non-null count:** use
    `COUNT(column)`.
7.  **Assuming `LIMIT` gives the highest values without `ORDER BY`:** it
    does not.
8.  **Ignoring ties:** choose `ROW_NUMBER`, `RANK`, or `DENSE_RANK`
    based on the requirement.
9.  **Using `NOT IN` with possible nulls:** consider `NOT EXISTS`.
10. **Turning a left join into an inner join unintentionally:** check
    filters on the right table.
11. **Integer division:** cast to `NUMERIC` or use a decimal constant.
12. **Wrong date boundary:** use a half-open timestamp range.
13. **Missing alias for a derived table:** add `AS alias`.
14. **Using a SELECT alias in WHERE:** repeat the expression or use a
    subquery/CTE.
15. **Forgetting duplicate behavior in UNION:** use `UNION ALL` when
    duplicates should remain.
16. **Relying on default row order:** specify `ORDER BY`.
17. **Unstable window ordering:** add a tie-breaker when needed.
18. **Confusing window functions with aggregates:** aggregates collapse
    groups; window functions preserve rows.
19. **Assuming a CTE is always faster:** optimize based on plans and
    measurements.
20. **Using the wrong dialect:** verify the platform is running
    PostgreSQL if using PostgreSQL-specific syntax.

Debug systematically: 1. Run the inner query by itself. 2. Check the
number of rows after each join. 3. Verify join keys and whether
duplicates multiply rows. 4. Inspect null behavior. 5. Test one small
example by hand. 6. Check edge cases and tie behavior. 7. Read the exact
error message and line/position. 8. Use `EXPLAIN` for performance
questions.

# 31. Suggested practice plan

A practical 6-week sequence, adjustable to your schedule:

### Week 1: Core querying

-   `SELECT`, aliases, `WHERE`, operators, `DISTINCT`
-   `ORDER BY`, `LIMIT`, `OFFSET`
-   `INSERT`, `UPDATE`, `DELETE`
-   `NULL`, `COALESCE`, `CASE`
-   Goal: 20--30 easy problems

### Week 2: Aggregation and functions

-   `COUNT`, `SUM`, `AVG`, `MIN`, `MAX`
-   `GROUP BY`, `HAVING`, conditional aggregation
-   String, numeric, and date functions
-   Goal: 20--30 easy/intermediate problems

### Week 3: Joins

-   Inner, left, self, and multi-table joins
-   Unmatched rows and anti-joins
-   One-to-many and many-to-many relationships
-   Goal: 20--30 join problems

### Week 4: Subqueries and CTEs

-   Scalar, correlated, `EXISTS`, `NOT EXISTS`, `IN`
-   Set operations
-   CTEs and recursive CTE basics
-   Goal: 15--25 intermediate problems

### Week 5: Window functions

-   `ROW_NUMBER`, `RANK`, `DENSE_RANK`
-   `LAG`, `LEAD`, running aggregates
-   Top N per group, latest row per group
-   Goal: 15--25 intermediate problems

### Week 6: Advanced patterns and review

-   Date ranges, percentages, duplicates, gaps/islands
-   `DISTINCT ON`, `FILTER`, `generate_series`
-   Review wrong answers and write clean solutions
-   Begin timed mixed-topic sets

Do not measure mastery by how many topics you have read. Measure it by
whether you can identify the right pattern and write the query without
looking at a solution.

# 32. Quick reference sheet

``` sql
-- Select
SELECT col1, col2 FROM table_name;

-- Filter
SELECT * FROM table_name WHERE condition;

-- Unique values
SELECT DISTINCT col FROM table_name;

-- Sort / top N
SELECT * FROM table_name ORDER BY col DESC LIMIT 10;

-- Insert
INSERT INTO table_name (col1, col2) VALUES (value1, value2);

-- Update
UPDATE table_name SET col = value WHERE id = 1;

-- Delete
DELETE FROM table_name WHERE id = 1;

-- Group
SELECT category, COUNT(*)
FROM table_name
GROUP BY category
HAVING COUNT(*) > 1;

-- Join
SELECT *
FROM a
JOIN b ON b.a_id = a.id;

-- Left join
SELECT *
FROM a
LEFT JOIN b ON b.a_id = a.id;

-- No match
SELECT a.*
FROM a
WHERE NOT EXISTS (
  SELECT 1 FROM b WHERE b.a_id = a.id
);

-- CTE
WITH x AS (SELECT ...)
SELECT * FROM x;

-- Rank
SELECT t.*,
       DENSE_RANK() OVER (PARTITION BY group_id ORDER BY score DESC) AS rnk
FROM t;

-- Null-safe fallback
SELECT COALESCE(col, 'Unknown') FROM table_name;

-- Transaction
BEGIN;
-- statements
COMMIT; -- or ROLLBACK;
```

------------------------------------------------------------------------

## Final learning advice

1.  Keep a `.sql` file per topic in VS Code, such as
    `01_select_where.sql`, `02_aggregates.sql`, `03_joins.sql`, and so
    on.
2.  Type examples rather than merely reading them.
3.  Predict the result before executing each query.
4.  For every LeetCode problem, explain why your query handles
    duplicates, nulls, and ties.
5.  Learn standard SQL patterns first, then PostgreSQL-specific tools.
6.  Revisit wrong answers after a day or two.
7.  Keep PostgreSQL documentation nearby:
    https://www.postgresql.org/docs/current/

**Best next step:** Work through sections 7--16 in order while
practicing with small tables. Then study subqueries, CTEs, and window
functions; these are especially important for intermediate and advanced
SQL problems.
