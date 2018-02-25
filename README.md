## FLAGS and SOLUTIONS

* **Cloning - Read-Access:** 
    - N/A

* **Cloning - Write-Access:** 
    - N/A

* **PIN Bypass - Read-Access:**
    - Bank verifies hashed PIN against db.

* **PIN Bypass - Write-Access:**
    - Bank verifies hashed PIN against db.

* **Skimming - Read-Access:**
    - Card signs random challenge request

* **Skimming - Write-Access:**
    - Card signs random challenge request

* **ATM Exploit:**
    - Bank verifies card_id and account balance.
    - Bank sends signed message of bills to give out to ATM which is forwared to HSM
    - HSM verifies signed message, only gives out bills if signature is valid
* **PIN Extraction:**
    - PIN is not stored on card.

* **Data Breach:**
    - Bank contains db of hashed data.