# Order Book Simulatior Specification

**** Work in progress. ****

### Overview

An order book is a list of open buy and sell orders for a particular security, organized by specific attributes such as price or quantity. It is a record of market depth and displays the overall supply and demand for the security. This project offers a robust and comprehensive order book simulator tool for various use cases.

**Supported Order Types**

The simulator accepts various types of buy and sell orders

1. *Market* - order executes imediately at the best available price
2. *Limit* - order executes at a specified price or better
3. *Stop* - order that executes when a particular price is reached
4. *Fill-Or-Kill* - order to be executed immediately, otherwised canceled
5. *Immediate-Or-Cancel* - order to fill as much as possible immediately, remainder is canceled
6. *Iceberg* - large order revealed in smaller chunks
