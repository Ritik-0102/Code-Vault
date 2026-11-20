# PostgreSQL Notes

# Part A — Foundations

## 1. What are SQL and PostgreSQL?

- **Database:** an organised collection of data.
- **DBMS:** software that stores and manages databases.
- **Relational database:** stores data in tables that can be related through keys.
- **SQL:** the language used to create, read, change, and manage relational data.
- **PostgreSQL:** a relational DBMS that understands SQL and adds features such as `ILIKE`, `RETURNING`, `DISTINCT ON`, `FILTER`, and regular-expression operators.

SQL is *declarative*: you describe the result you want; PostgreSQL decides how to retrieve it.

### Basic writing rules

- SQL keywords are commonly written in uppercase. They are generally case-insensitive.
- Unquoted PostgreSQL identifiers are folded to lowercase. Prefer names such as `student_id`.
- Use single quotes for text and date literals: `'Ritik'`, `DATE '2026-01-01'`.
- Double quotes are for identifiers and are usually avoidable.
- End statements with `;`.
- `--` starts a one-line comment; `/* ... */` makes a block comment.
- A result has no guaranteed order without `ORDER BY`.
- Use `IS NULL`, not `= NULL`.
- Include column names in `INSERT` statements.
- Check the `WHERE` clause before running `UPDATE` or `DELETE`.

```sql
-- Show students whose marks are at least 80, highest marks first
SELECT name, marks
FROM students
WHERE marks >= 80
ORDER BY marks DESC;
```
**Result:** the `name` and `marks` of qualifying students, sorted from highest to lowest.

## 2. SQL statement categories

| Category | Purpose | Common statements |
|---|---|---|
| DDL | Define/change structure | `CREATE`, `ALTER`, `DROP`, `TRUNCATE` |
| DML | Change data | `INSERT`, `UPDATE`, `DELETE`, `MERGE` |
| DQL | Read data (common teaching label) | `SELECT` |
| DCL | Permissions | `GRANT`, `REVOKE` |
| TCL | Transactions | `BEGIN`, `COMMIT`, `ROLLBACK`, `SAVEPOINT` |

Some books classify `SELECT` under DML; calling it DQL is a common teaching convention.

## 3. Database objects and relationships

- **Database:** named container for database objects.
- **Schema:** namespace inside a database; the common default is `public`.
- **Table:** rows and columns.
- **Row:** one record.
- **Column:** one property of a record.
- **Primary key:** uniquely identifies a row.
- **Foreign key:** connects a row to a key in another table.
- **View:** saved query definition.
- **Index:** data structure that can speed up certain lookups.
- **Sequence/identity:** generates values, often IDs.
- **Function, procedure, trigger:** programmable database objects.

Useful PostgreSQL inspection queries:

```sql
SELECT current_database(); -- e.g. dbms_practice
SELECT current_schema();   -- e.g. public
SELECT CURRENT_USER;       -- e.g. postgres
SELECT version();          -- PostgreSQL server version and platform
```

**Result:** one value per query describing the current connection/server.

## 4. Data types

Choose a type that matches the meaning of the value.

### Numbers

| Type | Use |
|---|---|
| `SMALLINT` | small whole number |
| `INTEGER` / `INT` | normal whole number |
| `BIGINT` | large whole number |
| `NUMERIC(p,s)` / `DECIMAL(p,s)` | exact decimal |
| `REAL`, `DOUBLE PRECISION` | approximate floating-point number |
| `SERIAL`, `BIGSERIAL` | older sequence-backed ID shorthand |

`NUMERIC(p,s)` means **p total digits** and **s digits after the decimal point**. For example, `NUMERIC(8,2)` can store values such as `123456.78`. `NUMERIC(2)` does **not** mean two decimal places.

```sql
SELECT 5 / 2 AS integer_result,
       5::NUMERIC / 2 AS decimal_result;
```
**Result:** `2 | 2.5000000000000000`.

### Text

- `TEXT`: variable-length text; a good default in PostgreSQL.
- `VARCHAR(n)`: variable-length text with a maximum length.
- `CHAR(n)`: fixed-width, blank-padded text; uncommon for normal application fields.

### Other types

- `BOOLEAN`: `TRUE`, `FALSE`, or `NULL`.
- `DATE`: calendar date.
- `TIME`: time of day.
- `TIMESTAMP`: date and time without time-zone-aware instant semantics.
- `TIMESTAMPTZ`: represents an instant; display depends on session time zone.
- `INTERVAL`: duration.
- `UUID`: unique identifier.
- `JSON` / `JSONB`: JSON data; `JSONB` is usually more useful for querying/indexing.
- `BYTEA`: binary data.
- Arrays such as `INTEGER[]`.
- `INET` / `CIDR`: network addresses/ranges.

### Type conversion (casting)

```sql
SELECT CAST('123' AS INTEGER), '45.6'::NUMERIC(5,2);
```
**Result:** `123 | 45.60`.

Use `::type` or `CAST(value AS type)` to make conversions explicit.

## 5. Creating databases and tables

Connect to a database before creating ordinary tables. `CREATE DATABASE` is normally run outside a transaction block.

```sql
CREATE DATABASE sql_practice;
```
**Result:** database `sql_practice` is created if the name is available and permissions allow it.

Create a table:

```sql
CREATE TABLE students (
    student_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    age INTEGER CHECK (age >= 0),
    city TEXT,
    marks INTEGER CHECK (marks BETWEEN 0 AND 100),
    created_at TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP
);
```
**Result:** an empty `students` table is created with six columns and the listed rules.

Insert sample data used in many examples below:

```sql
INSERT INTO students (student_id, name, age, city, marks)
VALUES
    (1, 'Ritik', 20, 'Jaipur', 85),
    (2, 'Aman', 21, 'Delhi', 76),
    (3, 'Priya', 19, 'Mumbai', 92),
    (4, 'Neha', 20, 'Delhi', 88),
    (5, 'Karan', 19, NULL, 67);
```
**Result:** `INSERT 0 5` — five rows added.

| student_id | name | age | city | marks |
|---:|---|---:|---|---:|
| 1 | Ritik | 20 | Jaipur | 85 |
| 2 | Aman | 21 | Delhi | 76 |
| 3 | Priya | 19 | Mumbai | 92 |
| 4 | Neha | 20 | Delhi | 88 |
| 5 | Karan | 19 | NULL | 67 |

Create a table from a query:

```sql
CREATE TABLE high_scorers AS
SELECT student_id, name, marks
FROM students
WHERE marks >= 85;
```
**Result:** a new table containing Ritik (85), Priya (92), and Neha (88). `CREATE TABLE AS` does not automatically copy all source constraints and indexes.

Temporary table:

```sql
CREATE TEMP TABLE work_list (id INTEGER, note TEXT);
```
**Result:** a temporary table available to the current session; normally removed when the session ends.

## 6. Constraints and keys

Constraints are rules enforced by the database.

| Constraint | Meaning |
|---|---|
| `PRIMARY KEY` | unique and not null row identifier |
| `FOREIGN KEY` | value must match a referenced key (subject to nullability/actions) |
| `UNIQUE` | prevents duplicate key values |
| `NOT NULL` | value is required |
| `CHECK` | value must satisfy a condition |
| `DEFAULT` | supplies a value when the column is omitted or `DEFAULT` is used |

Examples:

```sql
CREATE TABLE departments (
    department_id INTEGER PRIMARY KEY,
    department_name TEXT NOT NULL UNIQUE
);
```
**Result:** empty `departments` table; department IDs are unique/non-null and names are required/unique.

```sql
CREATE TABLE enrollments (
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    department_id INTEGER REFERENCES departments(department_id),
    enrolled_on DATE DEFAULT CURRENT_DATE,
    PRIMARY KEY (student_id, department_id)
);
```
**Result:** empty table. The pair `(student_id, department_id)` must be unique; deleting a referenced student deletes their enrollment rows because of `ON DELETE CASCADE`.

Important details:
- A **composite key** uses more than one column, e.g. `PRIMARY KEY (student_id, course_id)`.
- A `UNIQUE` constraint allows multiple `NULL`s by default in PostgreSQL. PostgreSQL also supports `NULLS NOT DISTINCT` in supported versions.
- A `CHECK` expression passes when it is true or unknown; add `NOT NULL` if null must be rejected.
- A default is not applied when you explicitly insert `NULL`.
- Prefer identity columns for new auto-generated numeric IDs:

```sql
CREATE TABLE products (
    product_id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    product_name TEXT NOT NULL
);
```
**Result:** an empty table; PostgreSQL generates `product_id` values on inserts. `GENERATED BY DEFAULT AS IDENTITY` is more permissive about explicit IDs.

## 7. CRUD — INSERT, SELECT, UPDATE, DELETE

CRUD = Create, Read, Update, Delete.

### INSERT

```sql
INSERT INTO students (student_id, name, age, city, marks)
VALUES (6, 'Isha', 20, 'Pune', 81);
```
**Result:** `INSERT 0 1`; one row is added.

Insert multiple rows with one `VALUES` list; list columns explicitly so the value order is clear.

Insert from another query:

```sql
INSERT INTO high_scorers (student_id, name, marks)
SELECT student_id, name, marks
FROM students
WHERE marks >= 85;
```
**Result:** copies qualifying rows into `high_scorers`; `INSERT 0 n` reports the number inserted. Running it repeatedly may cause duplicates unless a key/constraint prevents them.

### SELECT

```sql
SELECT name, marks FROM students;
```
**Result:** five rows with only the `name` and `marks` columns.

```sql
SELECT * FROM students;
```
**Result:** all columns and rows. Prefer explicit columns when the exact output matters.

Aliases rename output columns or table references:

```sql
SELECT name AS student_name, marks AS score
FROM students AS s;
```
**Result:** the same five rows, with output headings `student_name` and `score`.

### UPDATE

```sql
UPDATE students
SET marks = 90
WHERE student_id = 1
RETURNING *;
```
**Result:** the updated Ritik row is returned with `marks = 90`; command status `UPDATE 1`.

Update more than one column:

```sql
UPDATE students
SET city = 'Pune', marks = 80
WHERE student_id = 2;
```
**Result:** Aman is now in Pune with 80 marks; `UPDATE 1`.

**Safety:** run a matching `SELECT` with the same `WHERE` condition before a large update.

### DELETE

```sql
DELETE FROM students
WHERE student_id = 6
RETURNING *;
```
**Result:** the deleted Isha row is returned; `DELETE 1`.

```sql
DELETE FROM students;
```
**Result:** every row is removed, but the table remains. Never omit `WHERE` accidentally.

### UPSERT — `ON CONFLICT`

Insert a row, or update it if its key already exists:

```sql
INSERT INTO students (student_id, name, age, city, marks)
VALUES (1, 'Ritik', 20, 'Jaipur', 90)
ON CONFLICT (student_id)
DO UPDATE SET marks = EXCLUDED.marks
RETURNING *;
```
**Result:** student 1 is returned with marks 90. `EXCLUDED` means the proposed insert row that caused the conflict.

## 8. Filtering rows with WHERE

`WHERE` keeps only rows whose condition is true.

### Comparison operators

`=` equal · `<>` or `!=` not equal · `>` greater · `<` less · `>=` greater/equal · `<=` less/equal.

```sql
SELECT name FROM students WHERE marks >= 80;
```
**Result:** Ritik, Priya, Neha.

```sql
SELECT name FROM students WHERE city <> 'Delhi';
```
**Result:** Ritik and Priya. Karan's `NULL` city is not returned because a comparison with `NULL` is unknown.

### Logical operators

- `AND`: both conditions must be true.
- `OR`: at least one must be true.
- `NOT`: reverses true/false (unknown remains unknown).

```sql
SELECT name FROM students
WHERE city = 'Delhi' AND marks >= 80;
```
**Result:** Neha.

```sql
SELECT name FROM students
WHERE city = 'Delhi' OR city = 'Mumbai';
```
**Result:** Aman, Priya, Neha.

Use parentheses when mixing `AND` and `OR`. `AND` is evaluated before `OR`.

### BETWEEN

Inclusive at both ends:

```sql
SELECT name FROM students WHERE marks BETWEEN 70 AND 90;
```
**Result:** Ritik, Aman, Neha. Equivalent to `marks >= 70 AND marks <= 90`.

### IN and NOT IN

```sql
SELECT name FROM students WHERE city IN ('Delhi', 'Jaipur');
```
**Result:** Ritik, Aman, Neha.

```sql
SELECT name FROM students WHERE city NOT IN ('Delhi', 'Jaipur');
```
**Result:** Priya. `NULL` city is not included.

**Important:** if a `NOT IN` subquery returns even one `NULL`, the comparison can become unknown and unexpectedly return no rows. `NOT EXISTS` is often safer for checking that no matching row exists.

### DISTINCT

```sql
SELECT DISTINCT city FROM students ORDER BY city;
```
**Result:** `Delhi`, `Jaipur`, `Mumbai`, `NULL` — each distinct city value appears once.

```sql
SELECT DISTINCT city, age FROM students;
```
**Result:** unique `(city, age)` combinations, not unique cities alone.

## 9. LIKE and ILIKE — simple wildcard matching

`LIKE` searches using two wildcard symbols:
- `%` = zero or more characters.
- `_` = exactly one character.
- `ILIKE` is PostgreSQL's case-insensitive version.

```sql
SELECT name FROM students WHERE name LIKE 'R%';
```
**Result:** Ritik — names beginning with uppercase R.

```sql
SELECT name FROM students WHERE name LIKE '%a';
```
**Result:** Neha — names ending in lowercase `a` (case-sensitive).

```sql
SELECT name FROM students WHERE name ILIKE 'r%';
```
**Result:** Ritik — case-insensitive prefix match.

```sql
SELECT name FROM students WHERE name LIKE '_a%';
```
**Result:** Karan — second character is `a`.

`LIKE` is **not** regular-expression matching. Use Regex when the rule needs character classes, repetition rules, or exact start/end constraints.

## 10. Regular expressions (Regex) in PostgreSQL

A **regular expression** is a pattern that describes what text should look like. It is useful for validation, searching, and replacing text.

### PostgreSQL regex operators

| Operator | Meaning |
|---|---|
| `~` | matches regex; case-sensitive |
| `~*` | matches regex; case-insensitive |
| `!~` | does not match regex |
| `!~*` | does not match regex; case-insensitive |

```sql
SELECT 'ritik@gmail.com' ~ 'gmail';
```
**Result:** `TRUE`.

```sql
SELECT 'RITIK@gmail.com' ~ 'ritik';
```
**Result:** `FALSE`, because `~` is case-sensitive.

```sql
SELECT 'RITIK@gmail.com' ~* 'ritik';
```
**Result:** `TRUE`, because `~*` ignores letter case.

### Regex symbols you should know

| Symbol/pattern | Meaning | Example |
|---|---|---|
| `^` | start of string | `^A` matches `Apple`, not `Cat` |
| `$` | end of string | `com$` matches `mail.com` |
| `[ABC]` | one character: A or B or C | `[ABC]at` |
| `[A-Z]` | one uppercase English letter | `R` |
| `[a-z]` | one lowercase English letter | `i` |
| `[A-Za-z]` | one English letter | `R` or `i` |
| `[0-9]` | one digit | `7` |
| `[A-Za-z0-9]` | one letter or digit | `R`, `i`, or `7` |
| `*` | zero or more of previous item | `A*` |
| `+` | one or more of previous item | `A+` |
| `?` | zero or one of previous item | `colou?r` |
| `{2}` | exactly two repetitions | `[0-9]{2}` |
| `{2,4}` | two to four repetitions | `[0-9]{2,4}` |
| `.` | any one character | `a.b` matches `a1b` |
| `[.]` | a literal dot | `mail[.]com` |
| `\|` | alternation (OR) | `cat\|dog` |
| `( )` | groups part of a pattern | `(ab)+` |
| `[^0-9]` | one character that is not a digit | `[^0-9]` |

**Remember:** `*`, `+`, and `?` apply to the item immediately before them. `A*` can match zero A characters; `A+` requires at least one A.

### Small regex examples

```sql
SELECT 'Apple' ~ '^A';       -- TRUE: starts with A
SELECT 'Banana' ~ '^A';     -- FALSE: does not start with A
SELECT 'file.com' ~ 'com$'; -- TRUE: ends with com
SELECT 'A7B' ~ '^A.B$';     -- TRUE: A, any one character, B
SELECT 'AB' ~ '^A.B$';      -- FALSE: the middle character is missing
SELECT 'a12b' ~ '[0-9]+';   -- TRUE: contains one or more digits
```

### Regex vs LIKE

| Need | Use |
|---|---|
| Starts with `R` | `LIKE 'R%'` |
| Contains `abc` | `LIKE '%abc%'` |
| Exactly one character at a position | `LIKE '_'` or regex |
| First character must be a letter, then only certain characters | Regex |
| Must end in a precise pattern | Regex with `$` |

### LeetCode 1517 — valid email pattern

Requirements:
1. First character must be an English letter.
2. Remaining name characters may be letters, digits, `_`, `.`, or `-`.
3. Domain must be exactly `@leetcode.com`.
4. Match the entire email, not just a substring.

```sql
SELECT *
FROM Users
WHERE mail ~ '^[A-Za-z][A-Za-z0-9._-]*@leetcode[.]com$';
```
**Result:** only rows whose email follows all four rules.

Pattern breakdown:

| Part | Meaning |
|---|---|
| `^` | beginning of email |
| `[A-Za-z]` | first character is a letter |
| `[A-Za-z0-9._-]*` | zero or more allowed remaining name characters |
| `@leetcode` | exact domain prefix |
| `[.]com` | literal dot followed by `com` |
| `$` | end of email |

Examples:

| Email | Valid? | Reason |
|---|---|---|
| `ritik@leetcode.com` | Yes | starts with a letter; correct domain |
| `ritik123@leetcode.com` | Yes | digits allowed after first letter |
| `ritik.rana@leetcode.com` | Yes | dot allowed in name |
| `ritik_rana@leetcode.com` | Yes | underscore allowed |
| `123ritik@leetcode.com` | No | starts with a digit |
| `ritik@gmail.com` | No | wrong domain |
| `ritik@leetcode.in` | No | wrong ending |

**Tip:** `^` and `$` are essential for whole-string validation. Without them, a matching part somewhere inside a longer string may be enough.

### Regex functions

```sql
SELECT REGEXP_REPLACE('a12b34', '[0-9]+', '#', 'g');
```
**Result:** `a#b#`. The `g` flag replaces every match, not just the first.

```sql
SELECT REGEXP_MATCH('ritik123', '[0-9]+');
```
**Result:** `{123}` — the matched digit substring as an array.

## 11. String functions

| Function | Purpose | Example result |
|---|---|---|
| `LENGTH('SQL')` | character length | `3` |
| `LOWER('HELLO')` | lowercase | `hello` |
| `UPPER('hello')` | uppercase | `HELLO` |
| `INITCAP('hello world')` | capitalise word starts | `Hello World` |
| `TRIM('  hi  ')` | remove outer spaces | `hi` |
| `LEFT('Postgres',4)` | first 4 characters | `Post` |
| `RIGHT('Postgres',3)` | last 3 characters | `res` |
| `SUBSTRING('Postgres' FROM 1 FOR 4)` | part of string | `Post` |
| `REPLACE('banana','a','o')` | replace text | `bonono` |
| `POSITION('SQL' IN 'PostgreSQL')` | position (1-based) | `8` |
| `CONCAT('A','B')` | concatenate | `AB` |
| `'A' \|\| 'B'` | concatenate | `AB` |
| `SPLIT_PART('a,b,c', ',', 2)` | split and get part | `b` |
| `REPEAT('ha',3)` | repeat text | `hahaha` |
| `REVERSE('abc')` | reverse text | `cba` |
| `LPAD('42',5,'0')` | pad on left | `00042` |
| `RPAD('SQL',5,'.')` | pad on right | `SQL..` |

Examples:

```sql
SELECT UPPER('ritik'), LOWER('SQL'), INITCAP('hello world');
```
**Result:** `RITIK | sql | Hello World`.

```sql
SELECT CONCAT('Hello', ' ', 'World'), 'Hello' || ' ' || 'World';
```
**Result:** `Hello World | Hello World`.

LeetCode 1667 (Fix Names):

```sql
SELECT user_id,
       CONCAT(UPPER(LEFT(name, 1)), LOWER(SUBSTRING(name FROM 2))) AS name
FROM Users
ORDER BY user_id;
```
**Result:** each name has its first letter uppercase and all remaining letters lowercase, ordered by `user_id`.

## 12. Numeric functions and arithmetic

| Function | Meaning | Example result |
|---|---|---:|
| `ABS(-10)` | absolute value | 10 |
| `ROUND(12.345,2)` | round to 2 decimal places | 12.35 |
| `CEIL(4.2)` / `CEILING(4.2)` | round upward | 5 |
| `FLOOR(4.8)` | round downward | 4 |
| `POWER(2,3)` | exponent | 8 |
| `SQRT(25)` | square root | 5 |
| `MOD(10,3)` or `10 % 3` | remainder | 1 |
| `GREATEST(2,9,4)` | largest argument | 9 |
| `LEAST(2,9,4)` | smallest argument | 2 |

```sql
SELECT ROUND(12.345::NUMERIC, 2);
```
**Result:** `12.35`.

PostgreSQL detail: the two-argument `ROUND(value, decimal_places)` form expects `NUMERIC`. If a value is `DOUBLE PRECISION`, cast it: `ROUND(value::NUMERIC, 2)`.

**Integer division:** `5 / 2` gives `2`. Use `5::NUMERIC / 2` or `5.0 / 2` to keep the fractional part.

```sql
SELECT 5 / 2, 5::NUMERIC / 2;
```
**Result:** `2 | 2.5000000000000000`.

For percentages, multiply by `100.0` or cast to numeric before division. Use `NULLIF(denominator, 0)` to avoid division by zero.

## 13. Dates and times

### Common values and functions

```sql
SELECT CURRENT_DATE;
```
**Result:** today's date, e.g. `2026-11-20`.

```sql
SELECT CURRENT_TIMESTAMP, NOW();
```
**Result:** the current transaction timestamp (same value for both in a transaction), displayed in the session time zone.

### Date arithmetic

```sql
SELECT DATE '2026-02-01' + 7;
```
**Result:** `2026-02-08`.

```sql
SELECT DATE '2026-02-01' + INTERVAL '1 day';
```
**Result:** `2026-02-02 00:00:00`.

```sql
SELECT DATE '2026-02-01' - DATE '2026-01-01';
```
**Result:** `31` days.

Useful intervals: `INTERVAL '1 day'`, `INTERVAL '7 days'`, `INTERVAL '2 hours'`, `INTERVAL '1 month'`.

### Extracting and formatting

```sql
SELECT EXTRACT(YEAR FROM DATE '2026-11-20'),
       EXTRACT(MONTH FROM DATE '2026-11-20'),
       EXTRACT(DOW FROM DATE '2026-11-20');
```
**Result:** `2026 | 11 | 5` (DOW: Sunday 0 through Saturday 6).

```sql
SELECT TO_CHAR(DATE '2026-02-05', 'YYYY-MM');
```
**Result:** `2026-02` (text).

```sql
SELECT DATE_TRUNC('month', TIMESTAMP '2026-02-17 13:45:00');
```
**Result:** `2026-02-01 00:00:00`.

- `TO_CHAR` formats a date/time as text.
- `DATE_TRUNC` returns a date/time truncated to a unit.
- `TO_DATE(text, format)` parses text into a date.
- `TO_TIMESTAMP(text, format)` parses text into a timestamp.

### Date filtering

For a `DATE` column:

```sql
WHERE order_date BETWEEN DATE '2026-02-01' AND DATE '2026-02-28'
```
**Result:** rows dated from February 1 through February 28 inclusive.

For a timestamp column, use a half-open range:

```sql
WHERE created_at >= TIMESTAMP '2026-02-01 00:00:00'
  AND created_at <  TIMESTAMP '2026-03-01 00:00:00'
```
**Result:** every timestamp in February, including fractional seconds on February 28. For `TIMESTAMPTZ`, choose boundaries with the intended time zone.

**Important:** `TO_CHAR(date, 'YYYY-MM')` is useful for month labels/grouping; use date boundaries in `WHERE` when filtering actual dates.

## 14. Aggregate functions, GROUP BY, HAVING

Aggregate functions combine multiple rows into a summary.

| Function | Meaning |
|---|---|
| `COUNT(*)` | count all rows |
| `COUNT(column)` | count non-NULL values in column |
| `COUNT(DISTINCT column)` | count unique non-NULL values |
| `SUM(column)` | sum non-NULL values |
| `AVG(column)` | average non-NULL values |
| `MIN(column)` / `MAX(column)` | smallest/largest value |
| `STRING_AGG(value, delimiter)` | combine text values |
| `ARRAY_AGG(value)` | collect values into an array |

Using the sample `students` table:

```sql
SELECT COUNT(*), COUNT(city), COUNT(DISTINCT city), AVG(marks)
FROM students;
```
**Result:** `5 | 4 | 3 | 81.6`.

Why? Five rows; four non-null cities; three unique non-null cities; average marks = `(85+76+92+88+67)/5 = 81.6`.

### GROUP BY

Creates one result row per group:

```sql
SELECT city, COUNT(*) AS student_count
FROM students
GROUP BY city
ORDER BY city NULLS LAST;
```

**Result:**

| city | student_count |
|---|---:|
| Delhi | 2 |
| Jaipur | 1 |
| Mumbai | 1 |
| NULL | 1 |

Every selected column that is not aggregated generally belongs in `GROUP BY` (subject to PostgreSQL functional-dependency rules).

### HAVING

- `WHERE` filters individual rows **before** grouping.
- `HAVING` filters groups **after** aggregation.

```sql
SELECT city, COUNT(*) AS student_count
FROM students
GROUP BY city
HAVING COUNT(*) >= 2;
```
**Result:** `Delhi | 2`.

### Conditional aggregation

Count rows matching a condition without removing other rows:

```sql
SELECT COUNT(*) AS total,
       COUNT(*) FILTER (WHERE marks >= 80) AS high_scorers
FROM students;
```
**Result:** `5 | 3`.

Equivalent using `CASE`:

```sql
SELECT SUM(CASE WHEN marks >= 80 THEN 1 ELSE 0 END) AS high_scorers
FROM students;
```
**Result:** `3`.

`FILTER` is PostgreSQL's concise aggregate condition syntax. `SUM(...) FILTER (...)` returns `NULL` if no rows match; use `COALESCE` if you need zero.

### Percentages

```sql
SELECT ROUND(
    100.0 * COUNT(*) FILTER (WHERE marks >= 40) / NULLIF(COUNT(*), 0),
    2
) AS pass_percentage
FROM students;
```
**Result:** `100.00` for the sample data. If the table is empty, the result is `NULL` rather than a divide-by-zero error.

### Ordered string aggregation

```sql
SELECT city, STRING_AGG(name, ', ' ORDER BY name) AS students
FROM students
WHERE city IS NOT NULL
GROUP BY city
ORDER BY city;
```
**Result:** Delhi → `Aman, Neha`; Jaipur → `Ritik`; Mumbai → `Priya`.

For unique product names per date (LeetCode 1484):

```sql
SELECT sell_date,
       COUNT(DISTINCT product) AS num_sold,
       STRING_AGG(DISTINCT product, ',' ORDER BY product) AS products
FROM Activities
GROUP BY sell_date
ORDER BY sell_date;
```
**Result:** one row per date; count of unique products and their alphabetically sorted names joined by commas.

## 15. Joins

A join combines related rows from tables. Assume:

**departments**

| department_id | department_name |
|---:|---|
| 10 | Engineering |
| 20 | Sales |
| 30 | HR |

**employees**

| employee_id | employee_name | department_id | salary |
|---:|---|---:|---:|
| 1 | Asha | 10 | 70000 |
| 2 | Ben | 10 | 60000 |
| 3 | Cara | 20 | 50000 |
| 4 | Dev | NULL | 40000 |

### INNER JOIN

Only rows that match on both sides:

```sql
SELECT e.employee_name, d.department_name
FROM employees e
JOIN departments d ON e.department_id = d.department_id;
```
**Result:** Asha–Engineering, Ben–Engineering, Cara–Sales. Dev is omitted because there is no matching department.

### LEFT JOIN

Keeps every row from the left table; unmatched right columns become `NULL`:

```sql
SELECT e.employee_name, d.department_name
FROM employees e
LEFT JOIN departments d ON e.department_id = d.department_id;
```
**Result:** Asha–Engineering, Ben–Engineering, Cara–Sales, Dev–NULL.

### RIGHT JOIN

Keeps every row from the right table. Often rewritten as a `LEFT JOIN` by reversing table order.

### FULL OUTER JOIN

Keeps matched rows and unmatched rows from both sides.

```sql
SELECT e.employee_name, d.department_name
FROM employees e
FULL OUTER JOIN departments d ON e.department_id = d.department_id;
```
**Result:** all four employees and all three departments; unmatched side is `NULL`. HR appears with no employee.

### CROSS JOIN

Every combination of rows. If left has 4 rows and right has 3, result has 12 rows.

```sql
SELECT e.employee_name, d.department_name
FROM employees e CROSS JOIN departments d;
```
**Result:** 12 employee/department combinations.

### SELF JOIN

Join a table to itself, for example employee and manager:

```sql
SELECT e.employee_name AS employee, m.employee_name AS manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.employee_id;
```
**Result:** each employee with their manager's name; `manager` is `NULL` for employees without a manager. This example assumes `manager_id` exists.

### Important LEFT JOIN filter rule

This removes unmatched rows:

```sql
SELECT *
FROM employees e
LEFT JOIN departments d ON e.department_id = d.department_id
WHERE d.department_name = 'Engineering';
```
**Result:** only Engineering employees; the `WHERE` condition removes null-extended rows.

To keep every employee but match only Engineering departments, put the condition in `ON`:

```sql
SELECT *
FROM employees e
LEFT JOIN departments d
  ON e.department_id = d.department_id
 AND d.department_name = 'Engineering';
```
**Result:** all employees; department details appear only for Engineering matches.

### Joining more than two tables

```sql
SELECT s.name, c.course_name
FROM students s
JOIN enrollments e ON e.student_id = s.student_id
JOIN courses c ON c.course_id = e.course_id;
```
**Result:** one row per matching student-course enrollment.

Know relationship types:
- one-to-one,
- one-to-many,
- many-to-many (usually represented by a junction table such as `enrollments`).

## 16. Subqueries

A subquery is a query inside another query.

### Scalar subquery

Returns one value (zero rows gives `NULL`; more than one row causes an error in scalar context):

```sql
SELECT name, marks
FROM students
WHERE marks > (SELECT AVG(marks) FROM students);
```
**Result:** Priya and Neha (marks above 81.6).

### IN

Checks whether a value appears in a returned list:

```sql
SELECT name
FROM students
WHERE student_id IN (
    SELECT student_id
    FROM enrollments
    WHERE department_id = 10
);
```
**Result:** names of students enrolled in department 10.

### EXISTS and NOT EXISTS

`EXISTS` is true if the subquery returns at least one row. `SELECT 1` is conventional because the selected value is irrelevant.

```sql
SELECT s.name
FROM students s
WHERE EXISTS (
    SELECT 1 FROM enrollments e
    WHERE e.student_id = s.student_id
);
```
**Result:** students with at least one enrollment, each outer student appears once even if multiple enrollments exist.

```sql
SELECT s.name
FROM students s
WHERE NOT EXISTS (
    SELECT 1 FROM enrollments e
    WHERE e.student_id = s.student_id
);
```
**Result:** students with no enrollment.

### Correlated subquery

References a value from the current outer row:

```sql
SELECT e.employee_name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department_id = e.department_id
);
```
**Result:** employees paid above their own department's average.

### ANY and ALL

- `x > ANY (subquery)`: greater than at least one returned value.
- `x > ALL (subquery)`: greater than every returned value.

```sql
SELECT 80 > ANY (SELECT salary FROM employees WHERE department_id = 10);
```
**Result:** `TRUE` if 80 is greater than at least one salary in that department (with the example salaries above, `FALSE`).

### Subquery in FROM (derived table)

```sql
SELECT city, avg_marks
FROM (
    SELECT city, AVG(marks) AS avg_marks
    FROM students
    GROUP BY city
) AS city_summary
WHERE avg_marks >= 80;
```
**Result:** grouped cities whose average marks are at least 80. A derived table in PostgreSQL needs an alias.

### Multi-column/row-value IN

Useful when two columns together identify a row:

```sql
SELECT *
FROM Sales s
WHERE (s.product_id, s.year) IN (
    SELECT product_id, MIN(year)
    FROM Sales
    GROUP BY product_id
);
```
**Result:** the first-year row (or rows if a product has multiple rows in its first year) for each product.

## 17. Set operations

Each query must return the same number of columns with compatible types.

| Operation | What it does |
|---|---|
| `UNION` | combines results and removes duplicate rows |
| `UNION ALL` | combines results and keeps duplicates |
| `INTERSECT` | keeps rows appearing in both results |
| `EXCEPT` | rows in first result but not second |

```sql
SELECT city FROM students
UNION
SELECT city FROM employees;
```
**Result:** unique city values across both query results.

```sql
SELECT city FROM students
UNION ALL
SELECT city FROM employees;
```
**Result:** all rows from both results, including duplicates.

Use `UNION ALL` when duplicates are required or impossible and deduplication is unnecessary. Final sorting normally goes at the end of the compound query.

## 18. CTE — WITH

A Common Table Expression (CTE) names a query result for use by the statement that follows. It improves readability and helps split a complicated problem into steps. It is not automatically faster than a subquery.

```sql
WITH high_scorers AS (
    SELECT student_id, name, marks
    FROM students
    WHERE marks >= 85
)
SELECT *
FROM high_scorers
ORDER BY marks DESC;
```
**Result:** Priya (92), Neha (88), Ritik (85).

Multiple CTEs:

```sql
WITH city_avg AS (
    SELECT city, AVG(marks) AS avg_marks
    FROM students
    GROUP BY city
),
qualified AS (
    SELECT city, avg_marks
    FROM city_avg
    WHERE avg_marks >= 80
)
SELECT * FROM qualified;
```
**Result:** cities whose average marks are at least 80.

Recursive CTEs generate rows repeatedly, for example a number sequence or hierarchy traversal:

```sql
WITH RECURSIVE nums(n) AS (
    SELECT 1
    UNION ALL
    SELECT n + 1 FROM nums WHERE n < 5
)
SELECT n FROM nums;
```
**Result:** `1, 2, 3, 4, 5`.

Recursive structure: anchor query → `UNION ALL` → recursive query → stop condition. Prevent cycles in hierarchy/graph data.

## 19. Window functions

A window function calculates across related rows **without collapsing them** into one row per group. This is the key difference from `GROUP BY`.

General form:

```sql
function_name(...) OVER (
    PARTITION BY group_column
    ORDER BY sort_column
    ROWS BETWEEN ... AND ...
)
```

- `PARTITION BY`: restart calculation for each group.
- `ORDER BY`: define row order inside the window.
- Frame: define which rows contribute to the current calculation.

### ROW_NUMBER, RANK, DENSE_RANK

For values `100, 100, 80` in descending order:

| Value | ROW_NUMBER | RANK | DENSE_RANK |
|---:|---:|---:|---:|
| 100 | 1 | 1 | 1 |
| 100 | 2 | 1 | 1 |
| 80 | 3 | 3 | 2 |

- `ROW_NUMBER`: always unique sequence.
- `RANK`: ties share rank; next rank has a gap.
- `DENSE_RANK`: ties share rank; no gap.

```sql
SELECT employee_id, department_id, salary,
       ROW_NUMBER() OVER (PARTITION BY department_id ORDER BY salary DESC, employee_id) AS rn
FROM employees;
```
**Result:** each employee gets a row number within their department, highest salary first; employee ID breaks ties.

### Top N per group

```sql
WITH ranked AS (
    SELECT e.*,
           ROW_NUMBER() OVER (
               PARTITION BY department_id
               ORDER BY salary DESC, employee_id
           ) AS rn
    FROM employees e
)
SELECT *
FROM ranked
WHERE rn <= 2;
```
**Result:** up to two employees per department. Use `RANK`/`DENSE_RANK` if ties should include additional rows.

### LAG and LEAD

Read a value from a previous or following row:

```sql
SELECT student_id, marks,
       LAG(marks) OVER (ORDER BY student_id) AS previous_marks,
       LEAD(marks) OVER (ORDER BY student_id) AS next_marks
FROM students;
```
**Result:** each student's marks plus the previous/next student's marks; first previous and last next values are `NULL`.

### Running total

```sql
SELECT student_id, marks,
       SUM(marks) OVER (
           ORDER BY student_id
           ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
       ) AS running_total
FROM students;
```
**Result:** running totals `85, 161, 253, 341, 408` in student ID order.

### Moving average

```sql
SELECT student_id, marks,
       AVG(marks) OVER (
           ORDER BY student_id
           ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
       ) AS moving_avg
FROM students;
```
**Result:** average of the current row and up to two preceding rows.

### FIRST_VALUE and LAST_VALUE

`LAST_VALUE` can surprise beginners because the default frame often ends at the current row/peer group. To get the final value across the entire partition, specify the full frame:

```sql
LAST_VALUE(marks) OVER (
    PARTITION BY city
    ORDER BY marks
    ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
)
```
**Result:** the highest mark in each city (with ascending order), repeated for every row in that city.

Window results are usually filtered in an outer query/CTE because window functions are evaluated after `WHERE`.

## 20. NULL handling

`NULL` means missing, unknown, or not applicable. It is not zero and not an empty string.

Wrong:

```sql
SELECT * FROM students WHERE city = NULL;
```
**Result:** no rows; comparisons to `NULL` are unknown.

Correct:

```sql
SELECT * FROM students WHERE city IS NULL;
```
**Result:** Karan.

```sql
SELECT * FROM students WHERE city IS NOT NULL;
```
**Result:** Ritik, Aman, Priya, Neha.

### COALESCE

Returns the first non-NULL argument:

```sql
SELECT name, COALESCE(city, 'Unknown') AS city
FROM students;
```
**Result:** Karan's city displays as `Unknown`; other city values remain unchanged.

### NULLIF

Returns `NULL` when two arguments are equal:

```sql
SELECT 10 / NULLIF(0, 0);
```
**Result:** `NULL`, not a division-by-zero error.

### Three-valued logic

A condition can be TRUE, FALSE, or UNKNOWN. `WHERE` keeps only TRUE rows. For example, `marks <> 90` does not include rows where `marks` is `NULL`.

Null-safe comparisons:

- `a IS DISTINCT FROM b`: true when values differ; treats NULL as a comparable value.
- `a IS NOT DISTINCT FROM b`: true when values are equal, including NULL vs NULL.

## 21. CASE expressions

`CASE` is SQL's if/else expression. It returns a value.

```sql
SELECT name, marks,
       CASE
           WHEN marks >= 90 THEN 'Excellent'
           WHEN marks >= 75 THEN 'Good'
           WHEN marks >= 60 THEN 'Average'
           ELSE 'Needs improvement'
       END AS grade
FROM students;
```
**Result:** Ritik–Good, Aman–Good, Priya–Excellent, Neha–Good, Karan–Average.

Simple CASE:

```sql
SELECT name,
       CASE city
           WHEN 'Delhi' THEN 'North'
           WHEN 'Mumbai' THEN 'West'
           ELSE 'Other'
       END AS region
FROM students;
```
**Result:** Delhi students → North; Priya → West; Jaipur and NULL city → Other.

`CASE` can be used in `SELECT`, `ORDER BY`, `WHERE`, and inside aggregates.

## 22. DDL — changing table structure

Add a column:

```sql
ALTER TABLE students ADD COLUMN email TEXT;
```
**Result:** `email` column is added; existing rows get `NULL`.

Change a type:

```sql
ALTER TABLE students ALTER COLUMN marks TYPE NUMERIC(5,2);
```
**Result:** marks can now store decimal values such as `85.50` (conversion must be possible).

Set/remove default:

```sql
ALTER TABLE students ALTER COLUMN marks SET DEFAULT 0;
ALTER TABLE students ALTER COLUMN marks DROP DEFAULT;
```
**Result:** first sets the default to zero; second removes it.

Rename:

```sql
ALTER TABLE students RENAME COLUMN name TO student_name;
```
**Result:** column is renamed; its data remains.

Remove column/table:

```sql
ALTER TABLE students DROP COLUMN email;
DROP TABLE students;
```
**Result:** first removes the column and its data; second removes the table and all its data/definition.

### DELETE vs TRUNCATE vs DROP

| Command | Effect | WHERE? |
|---|---|---|
| `DELETE` | removes selected rows; table remains | Yes |
| `TRUNCATE` | removes all rows efficiently; table remains | No |
| `DROP` | removes the table object | No |

```sql
TRUNCATE TABLE students;
```
**Result:** all rows removed; table structure remains. These are destructive operations; use care.

## 23. Transactions and ACID

A transaction groups statements into one logical unit.

```sql
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE account_id = 1;
UPDATE accounts SET balance = balance + 100 WHERE account_id = 2;
COMMIT;
```
**Result:** both updates are saved together if the transaction commits successfully.

```sql
ROLLBACK;
```
**Result:** undoes uncommitted changes in the current transaction.

Savepoint:

```sql
BEGIN;
UPDATE students SET marks = marks + 1 WHERE student_id = 1;
SAVEPOINT after_first;
UPDATE students SET marks = marks + 1 WHERE student_id = 2;
ROLLBACK TO SAVEPOINT after_first;
COMMIT;
```
**Result:** student 1's update is saved; student 2's update is undone.

ACID:
- **Atomicity:** all-or-nothing.
- **Consistency:** constraints/rules remain satisfied.
- **Isolation:** concurrent transactions are controlled.
- **Durability:** committed changes persist.

PostgreSQL's default isolation level is Read Committed. Other important levels include Repeatable Read and Serializable. Learn MVCC, locks, deadlocks, and isolation anomalies after core querying.

## 24. Views, indexes, normalization, and performance

### Views

A view stores a query definition, not a separate copy of its result:

```sql
CREATE VIEW high_scorers AS
SELECT student_id, name, marks
FROM students
WHERE marks >= 85;
```
**Result:** view is created.

```sql
SELECT * FROM high_scorers;
```
**Result:** currently qualifying students; normal views reflect current underlying table data.

```sql
CREATE OR REPLACE VIEW high_scorers AS
SELECT student_id, name, marks FROM students WHERE marks >= 90;
```
**Result:** view definition is replaced to show only marks >= 90.

### Materialized views

Store a physical snapshot of a query result:

```sql
CREATE MATERIALIZED VIEW city_stats AS
SELECT city, COUNT(*) AS student_count, AVG(marks) AS avg_marks
FROM students
GROUP BY city;
```
**Result:** a saved result snapshot is created.

```sql
REFRESH MATERIALIZED VIEW city_stats;
```
**Result:** snapshot is recalculated from current source data. It can be stale until refreshed.

### Indexes

An index can speed up lookups, joins, and sorting, but uses storage and adds work to inserts/updates/deletes.

```sql
CREATE INDEX idx_students_city ON students(city);
```
**Result:** a B-tree index is created on `city`.

Other useful types:
- composite index: `CREATE INDEX ... ON table(col1, col2)`;
- unique index: rejects duplicate indexed values;
- partial index: indexes only rows satisfying a `WHERE` condition;
- expression index: e.g. `CREATE INDEX ... ON users(LOWER(email))`.

Column order matters in composite indexes. An index on `(city, marks)` is especially useful when queries filter by `city`, optionally followed by marks. Do not add indexes blindly.

Use:

```sql
EXPLAIN SELECT * FROM students WHERE city = 'Delhi';
```
**Result:** PostgreSQL's planned execution steps and estimated costs. `EXPLAIN ANALYZE` actually runs the query and reports measured timing/row counts.

### Normalization

Normalization organises data to reduce unnecessary duplication and update anomalies.

- **1NF:** each field contains one value; avoid repeating groups.
- **2NF:** in 1NF and every non-key attribute depends on the whole candidate key (relevant with composite keys).
- **3NF:** in 2NF and non-key attributes do not depend transitively on a key.
- **Denormalization:** intentionally duplicates/precomputes data for read performance, with consistency trade-offs.

Typical relationships:
- one-to-one,
- one-to-many,
- many-to-many using a junction table.

## 25. Useful PostgreSQL features

### RETURNING

Return rows changed by `INSERT`, `UPDATE`, or `DELETE`:

```sql
DELETE FROM students WHERE student_id = 5 RETURNING *;
```
**Result:** deleted student row is returned.

### DISTINCT ON

PostgreSQL-specific shortcut for one chosen row per group:

```sql
SELECT DISTINCT ON (product_id) product_id, change_date, new_price
FROM Products
ORDER BY product_id, change_date DESC;
```
**Result:** latest dated row per product (add a unique tie-breaker if dates can tie).

### FILTER

```sql
SELECT COUNT(*) FILTER (WHERE marks >= 80) FROM students;
```
**Result:** `3`.

### generate_series

Generate a sequence of values:

```sql
SELECT generate_series(1, 5);
```
**Result:** five rows: `1` through `5`.

### JSONB

`JSONB` stores JSON in a queryable binary representation. PostgreSQL provides operators such as `->` (JSON value) and `->>` (text value).

```sql
SELECT '{"name":"Ritik","age":20}'::JSONB ->> 'name';
```
**Result:** `Ritik`.

### Arrays

PostgreSQL supports array types and array operators. Use arrays when the data really represents a collection; for relational data with independent searchable items, a separate child table is often better.

### LATERAL

`LATERAL` lets a `FROM` subquery refer to preceding `FROM` items. It is useful for top-N related rows per parent. It is an advanced feature; learn it after joins and subqueries.

### Full-text search

PostgreSQL includes text-search types/functions such as `to_tsvector` and `plainto_tsquery`, useful for searching words in documents. This is different from substring `LIKE` and regex matching.

### Functions, procedures, triggers

- Function: reusable database routine that returns a value or table.
- Procedure: routine invoked with `CALL`, can support transaction control in allowed contexts.
- Trigger: automatically runs a function when a table event occurs.

These are useful in database application development but are not usually required for beginner LeetCode SQL.

---

# Part B — How PostgreSQL processes a query

## 26. Logical query processing order

A useful simplified order is:

1. `FROM` and `JOIN` — choose and combine source rows.
2. `WHERE` — filter individual rows.
3. `GROUP BY` — form groups.
4. Aggregate calculations.
5. `HAVING` — filter groups.
6. `SELECT` — calculate output expressions.
7. `DISTINCT` — remove duplicate output rows.
8. `ORDER BY` — sort output.
9. `LIMIT` / `OFFSET` — choose returned rows.

Example:

```sql
SELECT city, COUNT(*) AS total
FROM students
WHERE marks >= 70
GROUP BY city
HAVING COUNT(*) >= 2
ORDER BY total DESC;
```
**Result:** Delhi with 2 students. First low-mark rows are removed, then remaining rows are grouped, and only groups of at least two remain.

This is a *logical* explanation, not a promise about the physical execution plan.

---

# Part C — LeetCode and real-query patterns

## 27. Recognise the problem before writing SQL

| Problem wording | Pattern to consider |
|---|---|
| Show rows satisfying conditions | `SELECT` + `WHERE` |
| Count rows per group | `GROUP BY` + `COUNT(*)` |
| Count unique users/products | `COUNT(DISTINCT ...)` |
| Groups with at least N rows | `HAVING COUNT(*) >= N` |
| Include groups with zero matches | category table + `LEFT JOIN`, or fixed rows + `UNION ALL` |
| Percentage meeting a condition | conditional count × `100.0` / total |
| Keep rows with no related record | `NOT EXISTS` or `LEFT JOIN ... IS NULL` |
| Check if related row exists | `EXISTS` |
| Find first/last date per entity | `MIN` / `MAX` + join, or window ranking |
| Retrieve columns from latest row | `ROW_NUMBER()` or join to max date |
| Top row with tie rule | `ORDER BY aggregate DESC, tie_column ASC LIMIT 1` |
| Compare to group average | correlated subquery or window average |
| Previous/next row | `LAG` / `LEAD` |
| Running total | `SUM(...) OVER (ORDER BY ...)` |
| Consecutive rows | self join or `LAG` |
| Combine independent answer rows | `UNION ALL` |
| Validate text format | Regex (`~`) |
| Change text case | `UPPER`, `LOWER`, `INITCAP`, `SUBSTRING` |

## 28. Core reusable templates

### A. Count per group

```sql
SELECT category, COUNT(*) AS total
FROM Items
GROUP BY category;
```
**Result:** one row per category that exists, with its row count. Categories with zero rows do not appear.

### B. Groups above a threshold

```sql
SELECT class
FROM Courses
GROUP BY class
HAVING COUNT(*) >= 5;
```
**Result:** classes with at least five records.

### C. Conditional counts and percentage

```sql
SELECT
    COUNT(*) AS total,
    COUNT(*) FILTER (WHERE status = 'approved') AS approved,
    ROUND(
        100.0 * COUNT(*) FILTER (WHERE status = 'approved')
        / NULLIF(COUNT(*), 0), 2
    ) AS approved_percentage
FROM Transactions;
```
**Result:** one summary row; `NULL` percentage if there are no rows.

### D. LEFT JOIN to preserve unmatched rows

```sql
SELECT c.customer_id, COUNT(o.order_id) AS order_count
FROM Customers c
LEFT JOIN Orders o ON o.customer_id = c.customer_id
GROUP BY c.customer_id;
```
**Result:** every customer, including customers with zero orders. Use `COUNT(o.order_id)`, not `COUNT(*)`, because the unmatched left-join row still exists and would be counted by `COUNT(*)`.

### E. Find missing related rows

```sql
SELECT c.customer_id
FROM Customers c
WHERE NOT EXISTS (
    SELECT 1 FROM Orders o
    WHERE o.customer_id = c.customer_id
);
```
**Result:** customers with no matching order.

Equivalent anti-join:

```sql
SELECT c.customer_id
FROM Customers c
LEFT JOIN Orders o ON o.customer_id = c.customer_id
WHERE o.customer_id IS NULL;
```
**Result:** same unmatched customers, assuming `o.customer_id` is non-NULL for actual matching orders.

### F. Compare against an average

```sql
SELECT e.employee_id, e.salary
FROM Employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM Employees e2
    WHERE e2.department_id = e.department_id
);
```
**Result:** employees whose salary is greater than their own department average.

### G. Latest row per entity

```sql
WITH ranked AS (
    SELECT t.*,
           ROW_NUMBER() OVER (
               PARTITION BY customer_id
               ORDER BY order_date DESC, order_id DESC
           ) AS rn
    FROM Orders t
)
SELECT *
FROM ranked
WHERE rn = 1;
```
**Result:** one latest order per customer. The unique ID tie-breaker makes the choice deterministic.

### H. First date per entity

```sql
SELECT customer_id, MIN(order_date) AS first_order
FROM Orders
GROUP BY customer_id;
```
**Result:** one earliest date per customer. To retrieve other columns from that exact row, join back to the table or use `ROW_NUMBER()`.

### I. Second-highest distinct value

```sql
SELECT MAX(salary) AS SecondHighestSalary
FROM Employee
WHERE salary < (SELECT MAX(salary) FROM Employee);
```
**Result:** second-highest distinct salary; `NULL` if there is no second distinct value. Duplicates of the highest salary do not change the answer.

### J. Find duplicate values

```sql
SELECT email, COUNT(*) AS occurrences
FROM Person
GROUP BY email
HAVING COUNT(*) > 1;
```
**Result:** emails appearing more than once and their counts.

### K. Delete duplicates, keep smallest ID

```sql
DELETE FROM Person p1
USING Person p2
WHERE p1.email = p2.email
  AND p1.id > p2.id;
```
**Result:** duplicate rows with a larger ID are deleted; the smallest ID per email remains. Assumes IDs identify rows and email comparison should treat equal email strings as duplicates.

Alternative using a subquery:

```sql
DELETE FROM Person
WHERE id NOT IN (
    SELECT MIN(id)
    FROM Person
    GROUP BY email
);
```
**Result:** all but the smallest ID in each email group are deleted. Confirm null/unique-key assumptions before using this general pattern.

### L. Consecutive values

Three adjacent equal values by increasing ID:

```sql
SELECT DISTINCT a.num AS ConsecutiveNums
FROM Logs a
JOIN Logs b ON b.id = a.id + 1
JOIN Logs c ON c.id = b.id + 1
WHERE a.num = b.num AND b.num = c.num;
```
**Result:** each number that appears in at least three consecutive IDs, once.

Using `LAG`:

```sql
WITH checks AS (
    SELECT num,
           LAG(num, 1) OVER (ORDER BY id) AS prev1,
           LAG(num, 2) OVER (ORDER BY id) AS prev2
    FROM Logs
)
SELECT DISTINCT num
FROM checks
WHERE num = prev1 AND num = prev2;
```
**Result:** same qualifying numbers. “Consecutive” means adjacent rows in the specified order; it does not automatically mean consecutive calendar dates.

### M. Running total

```sql
SELECT person_name, turn, weight,
       SUM(weight) OVER (ORDER BY turn) AS total_weight
FROM Queue;
```
**Result:** each person with cumulative weight up to their turn.

To select the last person within a capacity:

```sql
SELECT person_name
FROM (
    SELECT person_name, turn,
           SUM(weight) OVER (ORDER BY turn) AS total_weight
    FROM Queue
) q
WHERE total_weight <= 1000
ORDER BY turn DESC
LIMIT 1;
```
**Result:** the last person in turn order whose cumulative weight does not exceed 1000. Sort by `turn`, the actual sequence column.

### N. Fixed categories, including zero counts

A normal `GROUP BY` cannot invent a category that has no rows. For a small fixed set:

```sql
SELECT 'Low Salary' AS category, COUNT(*) AS accounts_count
FROM Accounts WHERE income < 20000
UNION ALL
SELECT 'Average Salary', COUNT(*)
FROM Accounts WHERE income BETWEEN 20000 AND 50000
UNION ALL
SELECT 'High Salary', COUNT(*)
FROM Accounts WHERE income > 50000;
```
**Result:** always three rows; categories with no matches have count `0`.

### O. Choose one row with tie-breaking

```sql
SELECT u.name
FROM Users u
JOIN MovieRating mr ON mr.user_id = u.user_id
GROUP BY u.user_id, u.name
ORDER BY COUNT(*) DESC, u.name ASC
LIMIT 1;
```
**Result:** user with the most ratings; alphabetical name breaks a tie. Put the tie-breaker in the same `ORDER BY` before `LIMIT`.

### P. Monthly aggregation

```sql
SELECT TO_CHAR(trans_date, 'YYYY-MM') AS month,
       COUNT(*) AS trans_count,
       COUNT(*) FILTER (WHERE state = 'approved') AS approved_count,
       SUM(amount) AS trans_total,
       COALESCE(SUM(amount) FILTER (WHERE state = 'approved'), 0) AS approved_total
FROM Transactions
GROUP BY TO_CHAR(trans_date, 'YYYY-MM')
ORDER BY month;
```
**Result:** one row per month with total and approved counts/amounts. `COALESCE` changes an empty approved sum from `NULL` to zero.

### Q. First event and next-day activity

```sql
WITH first_login AS (
    SELECT player_id, MIN(event_date) AS first_date
    FROM Activity
    GROUP BY player_id
)
SELECT COUNT(*)
FROM first_login f
WHERE EXISTS (
    SELECT 1
    FROM Activity a
    WHERE a.player_id = f.player_id
      AND a.event_date = f.first_date + INTERVAL '1 day'
);
```
**Result:** number of players who logged in on the day immediately after their first login.

### R. Count unique items and concatenate names

```sql
SELECT sell_date,
       COUNT(DISTINCT product) AS num_sold,
       STRING_AGG(DISTINCT product, ',' ORDER BY product) AS products
FROM Activities
GROUP BY sell_date
ORDER BY sell_date;
```
**Result:** one row per date, with the number of unique products and alphabetically ordered product names.

### S. Email/text validation

```sql
SELECT *
FROM Users
WHERE mail ~ '^[A-Za-z][A-Za-z0-9._-]*@leetcode[.]com$';
```
**Result:** only emails satisfying the complete LeetCode 1517 pattern.

---

# Part D — Worked LeetCode scenarios from practice

These examples connect the concepts to common problem statements. Table names and columns follow the LeetCode problem schemas.

## 29. Join and unmatched-row scenarios

### LeetCode 1378 — Replace Employee ID With The Unique Identifier

**Idea:** keep every employee, even if no unique ID exists. Use `LEFT JOIN`.

```sql
SELECT eu.unique_id, e.name
FROM Employees e
LEFT JOIN EmployeeUNI eu
  ON eu.id = e.id;
```
**Result:** all employee names; `unique_id` is `NULL` where no matching row exists.

### LeetCode 1581 — Customer Who Visited but Did Not Make Any Transactions

**Idea:** visits with no matching transaction. Use `LEFT JOIN ... IS NULL`, then count visits per customer.

```sql
SELECT v.customer_id, COUNT(*) AS count_no_trans
FROM Visits v
LEFT JOIN Transactions t ON t.visit_id = v.visit_id
WHERE t.transaction_id IS NULL
GROUP BY v.customer_id;
```
**Result:** one row per customer with the number of visits that had no transaction.

### LeetCode 1661 — Average Time of Process per Machine

**Idea:** pair start and end rows from the same table using a self join; average end-start duration per machine.

```sql
SELECT a.machine_id,
       ROUND(AVG(b.timestamp - a.timestamp), 3) AS processing_time
FROM Activity a
JOIN Activity b
  ON a.machine_id = b.machine_id
 AND a.process_id = b.process_id
WHERE a.activity_type = 'start'
  AND b.activity_type = 'end'
GROUP BY a.machine_id;
```
**Result:** one average processing time per machine, rounded to three decimals.

### LeetCode 1280 — Students and Examinations

**Idea:** generate every student/subject combination, then left join exam attendance so zero counts are included.

```sql
SELECT s.student_id, s.student_name, sub.subject_name,
       COUNT(e.subject_name) AS attended_exams
FROM Students s
CROSS JOIN Subjects sub
LEFT JOIN Examinations e
  ON e.student_id = s.student_id
 AND e.subject_name = sub.subject_name
GROUP BY s.student_id, s.student_name, sub.subject_name
ORDER BY s.student_id, sub.subject_name;
```
**Result:** every student-subject pair, including pairs with zero exams. `COUNT(e.subject_name)` counts matched exam rows, not the preserved cross-join row.

## 30. Aggregation and percentage scenarios

### LeetCode 1934 — Confirmation Rate

**Idea:** count confirmations per user; divide confirmed rows by all requested rows. Preserve users with no confirmations.

```sql
SELECT s.user_id,
       ROUND(
           COALESCE(
               COUNT(c.user_id) FILTER (WHERE c.action = 'confirmed')::NUMERIC
               / NULLIF(COUNT(c.user_id), 0),
               0
           ),
           2
       ) AS confirmation_rate
FROM Signups s
LEFT JOIN Confirmations c ON c.user_id = s.user_id
GROUP BY s.user_id;
```
**Result:** one row per signup user; users without confirmation requests get `0.00`.

### LeetCode 1251 — Average Selling Price

**Idea:** join prices to units sold only when the purchase date falls inside the price period; calculate weighted average price.

```sql
SELECT p.product_id,
       ROUND(
           SUM(p.price * u.units)::NUMERIC / NULLIF(SUM(u.units), 0),
           2
       ) AS average_price
FROM Prices p
JOIN UnitsSold u
  ON u.product_id = p.product_id
 AND u.purchase_date BETWEEN p.start_date AND p.end_date
GROUP BY p.product_id;
```
**Result:** average selling price per product, weighted by units sold.

### LeetCode 1633 — Percentage of Users Attended a Contest

```sql
SELECT contest_id,
       ROUND(
           COUNT(DISTINCT user_id) * 100.0
           / (SELECT COUNT(*) FROM Users),
           2
       ) AS percentage
FROM Register
GROUP BY contest_id
ORDER BY percentage DESC, contest_id;
```
**Result:** each contest's percentage of all users who registered, highest percentage first.

### LeetCode 1211 — Queries Quality and Percentage

**Idea:** average `rating / position`; count ratings below 3 as a percentage.

```sql
SELECT query_name,
       ROUND(AVG(rating::NUMERIC / position), 2) AS quality,
       ROUND(
           COUNT(*) FILTER (WHERE rating < 3) * 100.0 / COUNT(*),
           2
       ) AS poor_query_percentage
FROM Queries
GROUP BY query_name;
```
**Result:** one row per query name with quality and poor-query percentage.

### LeetCode 1174 — Immediate Food Delivery II

**Idea:** first order date per customer; calculate the percentage of those first orders that match preferred date.

```sql
WITH first_orders AS (
    SELECT customer_id, MIN(order_date) AS first_date
    FROM Delivery
    GROUP BY customer_id
)
SELECT ROUND(
    COUNT(*) FILTER (
        WHERE d.order_date = d.customer_pref_delivery_date
    ) * 100.0 / COUNT(*),
    2
) AS immediate_percentage
FROM Delivery d
JOIN first_orders f
  ON f.customer_id = d.customer_id
 AND f.first_date = d.order_date;
```
**Result:** percentage of customers whose first order was scheduled for their preferred date.

## 31. Date and first/last-record scenarios

### LeetCode 1193 — Monthly Transactions I

```sql
SELECT TO_CHAR(trans_date, 'YYYY-MM') AS month,
       country,
       COUNT(*) AS trans_count,
       COUNT(*) FILTER (WHERE state = 'approved') AS approved_count,
       SUM(amount) AS trans_total,
       COALESCE(SUM(amount) FILTER (WHERE state = 'approved'), 0) AS approved_total
FROM Transactions
GROUP BY TO_CHAR(trans_date, 'YYYY-MM'), country
ORDER BY month, country;
```
**Result:** one row per month and country with transaction counts and totals.

### LeetCode 1141 — User Activity for the Past 30 Days I

For the inclusive period June 28 through July 27, 2019:

```sql
SELECT activity_date AS day,
       COUNT(DISTINCT user_id) AS active_users
FROM Activity
WHERE activity_date >= DATE '2019-06-28'
  AND activity_date <  DATE '2019-07-28'
GROUP BY activity_date;
```
**Result:** one row per date with distinct active users. The end boundary is exclusive, making the 30-day range clear.

### LeetCode 550 — Game Play Analysis IV

**Idea:** find each player's first login and check for a login exactly one day later.

```sql
WITH first_login AS (
    SELECT player_id, MIN(event_date) AS first_date
    FROM Activity
    GROUP BY player_id
)
SELECT ROUND(
    COUNT(*) FILTER (WHERE EXISTS (
        SELECT 1
        FROM Activity a
        WHERE a.player_id = f.player_id
          AND a.event_date = f.first_date + INTERVAL '1 day'
    ))::NUMERIC
    / NULLIF((SELECT COUNT(DISTINCT player_id) FROM Activity), 0),
    2
) AS fraction
FROM first_login f;
```
**Result:** fraction of players who returned the day after their first login, rounded to two decimals.

### LeetCode 1070 — Product Sales Analysis III

**Idea:** find first year per product, then return the matching sales row(s).

```sql
SELECT product_id, year AS first_year, quantity, price
FROM Sales s
WHERE year = (
    SELECT MIN(year)
    FROM Sales
    WHERE product_id = s.product_id
);
```
**Result:** first-year sales rows for each product, including quantity and price from that year.

### LeetCode 1164 — Product Price at a Given Date

**Idea:** latest change on or before 2019-08-16; products with no qualifying change use default price 10.

```sql
SELECT product_id, new_price AS price
FROM Products
WHERE (product_id, change_date) IN (
    SELECT product_id, MAX(change_date)
    FROM Products
    WHERE change_date <= DATE '2019-08-16'
    GROUP BY product_id
)
UNION ALL
SELECT DISTINCT product_id, 10 AS price
FROM Products
WHERE product_id NOT IN (
    SELECT product_id
    FROM Products
    WHERE change_date <= DATE '2019-08-16'
);
```
**Result:** one effective price per product on the target date. The second query branch includes products with no change on/before that date. This `NOT IN` is safe under the problem's non-null product ID constraint.

## 32. Ranking, CASE, and set-operation scenarios

### LeetCode 596 — Classes More Than 5 Students

```sql
SELECT class
FROM Courses
GROUP BY class
HAVING COUNT(*) >= 5;
```
**Result:** classes containing at least five rows.

### LeetCode 619 — Biggest Single Number

```sql
SELECT MAX(num) AS num
FROM (
    SELECT num
    FROM MyNumbers
    GROUP BY num
    HAVING COUNT(*) = 1
) AS single_values;
```
**Result:** largest number appearing exactly once; `NULL` if no number appears once.

### LeetCode 1045 — Customers Who Bought All Products

```sql
SELECT customer_id
FROM Customer
GROUP BY customer_id
HAVING COUNT(DISTINCT product_key) = (
    SELECT COUNT(*) FROM Product
);
```
**Result:** customers who bought every product. `DISTINCT` prevents repeated purchases from inflating the count.

### LeetCode 1731 — The Number of Employees Which Report to Each Employee

```sql
SELECT e.reports_to AS employee_id,
       m.name,
       COUNT(*) AS reports_count,
       ROUND(AVG(e.age)) AS average_age
FROM Employees e
JOIN Employees m ON m.employee_id = e.reports_to
GROUP BY e.reports_to, m.name
ORDER BY employee_id;
```
**Result:** each manager with number of direct reports and rounded average age of those reports.

### LeetCode 1789 — Primary Department for Each Employee

```sql
SELECT employee_id, department_id
FROM Employee
WHERE primary_flag = 'Y'
UNION
SELECT employee_id, department_id
FROM Employee
GROUP BY employee_id, department_id
HAVING COUNT(*) = 1;
```
**Result:** primary department for employees with multiple departments, plus their only department when they have one. Use the exact problem schema/constraints when applying this pattern.

### LeetCode 610 — Triangle Judgement

```sql
SELECT x, y, z,
       CASE
           WHEN x + y > z AND x + z > y AND y + z > x
           THEN 'Yes'
           ELSE 'No'
       END AS triangle
FROM Triangle;
```
**Result:** `Yes` only when all three pairwise sums are strictly greater than the remaining side.

### LeetCode 626 — Exchange Seats

```sql
SELECT
    CASE
        WHEN id % 2 = 1 AND id < (SELECT MAX(id) FROM Seat) THEN id + 1
        WHEN id % 2 = 0 THEN id - 1
        ELSE id
    END AS id,
    student
FROM Seat
ORDER BY id;
```
**Result:** students in adjacent seat IDs are swapped; the last student stays in place if the row count is odd. This assumes the problem's consecutive IDs begin at 1.

### LeetCode 1341 — Movie Rating

Two separate rankings are needed, combined with `UNION ALL`.

```sql
(SELECT u.name AS results
 FROM Users u
 JOIN MovieRating mr ON mr.user_id = u.user_id
 GROUP BY u.user_id, u.name
 ORDER BY COUNT(*) DESC, u.name ASC
 LIMIT 1)
UNION ALL
(SELECT m.title AS results
 FROM Movies m
 JOIN MovieRating mr ON mr.movie_id = m.movie_id
 WHERE mr.created_at >= DATE '2020-02-01'
   AND mr.created_at < DATE '2020-03-01'
 GROUP BY m.movie_id, m.title
 ORDER BY AVG(mr.rating) DESC, m.title ASC
 LIMIT 1);
```
**Result:** first row is the user with the most ratings (alphabetical tie-break); second row is the movie with the highest February 2020 average rating (alphabetical tie-break).

**Important tie rule:** tie-break columns must be included in the same `ORDER BY` before `LIMIT`. Sorting outside after a `LIMIT` cannot change which tied row was selected.

## 33. More problem-solving lessons

### `COUNT(*)` vs `COUNT(column)` vs `COUNT(DISTINCT column)`

For values `A, A, B, NULL`:
- `COUNT(*)` = 4 rows.
- `COUNT(value)` = 3 non-null values.
- `COUNT(DISTINCT value)` = 2 unique non-null values.

### Why `MAX(COUNT(*))` is usually invalid

You cannot directly nest one aggregate inside another at the same query level. First calculate counts per group, then select the maximum in an outer query or order by the count.

```sql
SELECT MAX(group_count)
FROM (
    SELECT category, COUNT(*) AS group_count
    FROM Items
    GROUP BY category
) q;
```
**Result:** largest group size.

### `WHERE` vs `HAVING` vs `FILTER`

- `WHERE`: remove source rows before grouping.
- `HAVING`: remove completed groups.
- `FILTER`: include only matching rows in one aggregate calculation while leaving other aggregates unaffected.

### `UNION` vs `UNION ALL`

`UNION` removes duplicate output rows; `UNION ALL` keeps them. If the problem asks for two answer rows even if their text happens to match, `UNION ALL` is generally the right choice.

### `NOT IN` vs `NOT EXISTS`

`NOT IN` can fail unexpectedly when the subquery includes `NULL`. `NOT EXISTS` checks for the absence of a matching row and is often the safer general anti-join.

### Grouping with related descriptive columns

When grouping by an ID and displaying a name, group by both ID and name for clarity:

```sql
SELECT department_id, department_name, COUNT(*)
FROM employees
JOIN departments USING (department_id)
GROUP BY department_id, department_name;
```
**Result:** one row per department with its employee count.

### Ordering is not automatic

Always add `ORDER BY` when the problem requires a particular output order. Do not assume insertion order or index order.

---

# Part E — Debugging and revision

## 34. Common mistakes

| Mistake | Correct thinking |
|---|---|
| `column = NULL` | use `IS NULL` |
| Using `WHERE COUNT(*) > ...` | use `HAVING` for aggregate conditions |
| Counting after a `LEFT JOIN` with `COUNT(*)` | count a non-null right-table key when zero matches should be zero |
| Using `COUNT(*)` when unique items are requested | use `COUNT(DISTINCT item)` |
| Forgetting zero-count categories | create the categories and `LEFT JOIN`, or use fixed `UNION ALL` queries |
| `NOT IN` subquery can return NULL | consider `NOT EXISTS` |
| Integer division for percentage | multiply by `100.0` or cast to numeric |
| Divide by zero | use `NULLIF(denominator, 0)` |
| PostgreSQL `ROUND(double, 2)` | cast to `NUMERIC` |
| `NUMERIC(2)` for two decimal places | use `NUMERIC(p,2)` if a fixed scale is needed |
| Filtering right table in `WHERE` after LEFT JOIN | move the condition into `ON` if unmatched left rows must remain |
| Selecting columns not grouped/aggregated | add them to `GROUP BY` or aggregate them |
| Scalar subquery returns multiple rows | make it scalar or use `IN`/`EXISTS`/join |
| Latest date but need other columns | join to the latest row or use `ROW_NUMBER()` |
| Tie not handled before `LIMIT` | add tie-break columns in the same `ORDER BY` |
| Assuming output order | use `ORDER BY` |
| Treating `LIKE` as Regex | learn wildcard rules vs regex operators |
| Forgetting `^`/`$` in validation | anchor the whole string |
| Using `.` for a literal dot in Regex | use `[.]` or escape it |
| Assuming CTE always makes query faster | CTE mainly improves readability; inspect plan if performance matters |

## 35. Debugging checklist before submitting

1. Does the query return exactly the required columns and aliases?
2. Should unmatched rows remain? Choose `LEFT JOIN` if yes.
3. Does the question want rows, unique users, or unique products?
4. Can `NULL` change a comparison, count, sum, or `NOT IN`?
5. Must categories with zero rows still appear?
6. Are row filters in `WHERE` and aggregate filters in `HAVING`/`FILTER`?
7. Are date boundaries inclusive/exclusive as required?
8. Are ties handled with the required tie-breaker before `LIMIT`?
9. Is output ordering explicitly required?
10. Can integer division or division by zero change the result?
11. Can a scalar subquery return more than one row?
12. What does “consecutive” mean in this problem: adjacent IDs, dates, or ordered rows?
13. Have you checked one-row, no-match, duplicate, tie, NULL, and boundary cases?

## 36. Quick reference sheet

| Task | SQL pattern |
|---|---|
| Filter | `WHERE condition` |
| Sort | `ORDER BY col ASC/DESC` |
| Top N | `ORDER BY ... LIMIT N` |
| Unique rows | `SELECT DISTINCT ...` |
| Match a list | `IN (...)` |
| Pattern with wildcards | `LIKE` / `ILIKE` |
| Regex match | `~` / `~*` |
| Null check | `IS NULL` / `IS NOT NULL` |
| Replace NULL | `COALESCE(value, fallback)` |
| Avoid zero denominator | `NULLIF(denominator, 0)` |
| Conditional output | `CASE WHEN ... THEN ... ELSE ... END` |
| Group rows | `GROUP BY` |
| Filter groups | `HAVING` |
| Conditional aggregate | `COUNT(*) FILTER (WHERE ...)` |
| Join matching rows | `INNER JOIN` |
| Keep all left rows | `LEFT JOIN` |
| No matching row | `NOT EXISTS` |
| Scalar result from query | `(SELECT ...)` |
| Named query step | `WITH name AS (...)` |
| Combine results, deduplicate | `UNION` |
| Combine results, keep duplicates | `UNION ALL` |
| Rank within group | `ROW_NUMBER() OVER (PARTITION BY ... ORDER BY ...)` |
| Previous row | `LAG()` |
| Next row | `LEAD()` |
| Running total | `SUM(x) OVER (ORDER BY ...)` |
| Month label | `TO_CHAR(date_col, 'YYYY-MM')` |
| Add one day | `date_col + INTERVAL '1 day'` |
| Round to 2 decimals | `ROUND(value::NUMERIC, 2)` |
| Join text values | `STRING_AGG(value, ',' ORDER BY value)` |
| Return changed rows | `RETURNING *` |

## 37. LeetCode practice index

| Problem | Main concept |
|---|---|
| 1378 | LEFT JOIN, missing match |
| 1581 | LEFT JOIN anti-match, GROUP BY |
| 197 | date/row filtering |
| 1661 | self join, time difference, AVG |
| 1280 | CROSS JOIN + LEFT JOIN, zero counts |
| 570 | self join / manager relation |
| 1934 | conditional aggregation, percentage |
| 1251 | date-range join, weighted average |
| 1633 | COUNT DISTINCT, percentage |
| 1211 | AVG, FILTER, CASE, percentage |
| 1193 | monthly grouping, TO_CHAR, FILTER, COALESCE |
| 1174 | first order per customer, percentage |
| 550 | first login, EXISTS, next-day interval |
| 1141 | inclusive 30-day date range, COUNT DISTINCT |
| 1070 | MIN year per product, correlated subquery |
| 596 | GROUP BY + HAVING |
| 619 | count occurrences, outer MAX |
| 1045 | COUNT DISTINCT compared with total products |
| 1731 | self join, COUNT, AVG, ROUND |
| 1789 | CASE / grouping / UNION |
| 610 | CASE and triangle inequalities |
| 180 | consecutive rows, self join or LAG |
| 1164 | latest change per product, row-value IN, UNION ALL |
| 1204 | running total with window function |
| 1907 | fixed categories and zero counts |
| 1978 | NOT IN / NOT EXISTS / anti-join |
| 626 | CASE, modulo, adjacent ID swap |
| 1341 | aggregate ranking, tie-break, UNION ALL |
| 1667 | UPPER, LOWER, LEFT, SUBSTRING |
| 196 | DELETE duplicates, keep minimum ID |
| 176 | second-highest distinct value |
| 1484 | COUNT DISTINCT, STRING_AGG |
| 1517 | Regex validation with `~`, anchors, character classes |

## 38. Suggested learning order

1. **Core querying:** SELECT, WHERE, DISTINCT, ORDER BY, LIMIT, NULL.
2. **Expressions:** CASE, string functions, numeric functions, dates.
3. **Aggregation:** COUNT, SUM, AVG, GROUP BY, HAVING, FILTER, percentages.
4. **Joins:** INNER, LEFT, self join, anti-join.
5. **Subqueries:** scalar, IN, EXISTS, correlated subqueries.
6. **CTEs and set operations:** WITH, UNION, UNION ALL.
7. **Window functions:** ROW_NUMBER, RANK, LAG, running totals.
8. **Advanced PostgreSQL:** Regex, DISTINCT ON, JSONB, indexes, transactions.
9. **Mixed practice:** solve without looking at templates; explain why edge cases work.

**Final principle:** Do not memorise SQL only by problem number. Identify the task — filter, group, join, find missing rows, find first/latest row, rank, calculate a percentage, or compare consecutive rows — then choose the matching pattern and test edge cases.
