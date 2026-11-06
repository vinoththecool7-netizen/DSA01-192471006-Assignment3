# Q4 Money arithmetic and stream operators

## Design and implementation

The hardened Money class stores signed long long paise and checks overflow before mutation. Negative results represent refunds/credits: 25 paise minus one rupee is -75 paise. Tests verify 75+50 paise carries to Rs 1.25 and the bill Rs 120.75+Rs 79.25 equals Rs 200.00. Addition, subtraction, +=, == and < operate on exact stored values.

+= is a member mutator returning Money& to *this for chaining. + takes the left operand by value and returns an independent value; - likewise returns a new value. Symmetric arithmetic/comparison operators are non-member friends with controlled access to private data. A member + translates a+b into a.operator+(b); the chosen free function resolves operator+(a,b).

<< and >> must be non-members for the desired stream-left syntax because the standard stream classes cannot be extended with new members. Returning stream references supports chaining. << uses integer formatting, including LLONG_MIN through unsigned magnitude, avoiding a signed negation overflow or double conversion. >> accepts an optional sign, integer digits and up to two fractional digits, validates the whole token, sets failbit on invalid input and preserves the old amount. It accepts plain decimals, not the printed Rs prefix, so this is not a round-trip serialisation pair. Constructor (rupees,p) uses algebraic signed parts; text parsing applies the leading minus to the whole decimal magnitude.

complete.cpp fills only the supplied TODO regions and matches the expected two-line output exactly. The skeleton's unchecked constructor and simple nonnegative formatting remain unchanged; money.hpp is the separate hardened implementation. Tests include signed endpoints, malformed decimals, extra precision, overflow, comparison, reference identity and failed-input preservation. io.cpp actually consumes io.stdin.txt and compares against its expected output.

## Experiment and engineering decision

One million additions of 10 paise give exactly 10,000,000 paise. The corresponding double loop adds 0.1 rupees and records its actual error (about +1.33288e-6 rupees in this run). Floating error depends on values and addition order; exact integer paise are preferred while the sum fits.

Named operations add(a,b) and equals(total,Money{200}) express the same checked arithmetic; operators let the bill read total=a+b. Money*Money would have currency-squared units and is deliberately absent. A dimensionless scalar or quantity times Money can make sense if rounding and overflow rules are defined.

With a non-explicit converting constructor, a non-member operator+(Money,Money) permits 100+m and m+100. A member permits conversion on its right operand, so m+100 works but 100+m cannot call a Money member. The submitted hardened constructor is explicit, intentionally requiring Money{100} in both cases; friendship does not override explicit.

## Alternative and complexity

Member, friend and named versions all have O(1) time/space for fixed-width stored values. A million operations is O(n) time, O(1) auxiliary space. Parsing an L-character token is O(L) time/token storage, distinct from the O(1) arithmetic itself. The class permits meaningful value operations without pretending that spelling an operator improves numeric precision. Run python3 scripts/validate.py --task Task04, optionally with --sanitize.
