pragma solidity ^0.8.0;

contract SimpleStorage {

    uint public number;

    // Function to store number
    function setNumber(uint _num) public {
        number = _num;
    }

    // Function to get number
    function getNumber() public view returns (uint) {
        return number;
    }
}










// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Student {

    string public name;
    uint public age;

    // Function to store student details
    function setStudent(string memory _name, uint _age) public {
        name = _name;
        age = _age;
    }

    // Function to retrieve student details
    function getStudent() public view returns (string memory, uint) {
        return (name, age);
    }
}

















// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract FundTransfer {

    address public owner;

    // Constructor ? sets deployer as owner
    constructor() {
        owner = msg.sender;
    }

    // Receive Ether into contract
    receive() external payable {}

    // Check contract balance
    function getBalance() public view returns (uint) {
        return address(this).balance;
    }

    // Transfer funds to another user
    function transferFunds(address payable _to, uint _amount) public {
        require(msg.sender == owner, "Only owner can transfer funds");
        require(address(this).balance >= _amount, "Insufficient balance");

        _to.transfer(_amount);
    }
}
