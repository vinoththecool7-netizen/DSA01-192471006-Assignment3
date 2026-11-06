# Q1 Constructors and constructor overloading

## Design and implementation

Book keeps its title, author and copy count private. The default constructor delegates to the full constructor with empty strings and zero copies; the explicit title-only overload delegates with author Unknown and one copy, an assumption for a donated book. The full constructor initialises every member in a member initializer list and rejects a negative count with invalid_argument. A throwing constructor does not leave a usable invalid Book. Zero copies is a valid empty record.

Object states after construction:

| Object | Title | Author | Copies |
|---|---|---|---|
| empty | empty string | empty string | 0 |
| donated | Donated Atlas | Unknown | 1 |
| full | C++ Primer | Lippman | 3 |

The compiler implicitly declares a default constructor when no user-declared constructor or constructor template exists. Declaring the title constructor therefore prevents an implicit no-argument constructor; the separate no_default experiment attempts Book books[3] and must fail. An implicitly declared/defaulted constructor can itself be deleted if a member or base cannot be default-constructed.

Initializer lists directly construct members, support const/reference members, and avoid default construction followed by assignment. Bases are initialised first, then data members in declaration order, regardless of list order. The reorder experiment deliberately lists second before first without reading an uninitialised value; the actual warning and printed 1 2 are saved.

## Explicit conversion experiment

A single-argument constructor should normally be explicit when automatic conversion would hide an object-creation decision. accept(std::string{"Title"}) works with the implicit wrapper but fails with explicit. Both source variants and actual compiler outcomes are retained. Direct construction Book{"Title"} still works.

## Alternative and complexity

A single constructor could use Book(std::string title="", std::string author="", int copies=0) with one validation point. Delegation also gives one validation point; it is incorrect to claim the overload design necessarily validates in more places. Default arguments would give a title-only donated record zero copies unless that business rule were changed; overloads express the distinct situations clearly.

With fixed-size fields or fixed-length strings both designs have O(1) object-creation overhead and object footprint. For arbitrary title/author lengths T and A, copying strings actually costs O(T+A) time and owned character storage in either design; moving supplied strings can avoid those copies. The assignment's O(1) statement is therefore a fixed-size abstraction, not a universal string-copy guarantee.

## Evidence

Run python3 scripts/validate.py --task Task01, optionally adding --sanitize. The evidence directories contain stdout, stderr, exact compilation commands, return codes and source digests. Negative-copy, explicit-conversion and missing-default checks are real experiments; the intentionally invalid sources use .cpp.txt so they do not break ordinary source builds.
