# cattle-feedtime-management
https://bineet2003.github.io/cattle-feedtime-management/

The represents a simple web page for managing cattle data.

The JavaScript code defines four functions: addData(), removeData(), displayData(), and displayDataByTime().

The addData() function is called when the "Add" button is clicked. It retrieves input values for cattle ID, cattle name, feed time, and food from the corresponding input fields. It creates a new cattle object with the retrieved values and adds it to an array called cattleList. The cattleList array is stored in the browser's local storage using localStorage.setItem(). An alert is displayed to indicate that the cattle data has been added successfully.

The removeData() function is called when the "Remove" button is clicked. It retrieves the cattle ID to remove from the corresponding input field. It retrieves the existing cattle data from local storage, removes the cattle object with the matching cattle ID from the cattleList array, and updates the local storage accordingly. An alert is displayed to indicate that the cattle data has been removed successfully.

The displayData() function is called when the "Display Data" button is clicked. It retrieves the cattle data from local storage and generates an HTML table to display the data. The table is sorted by cattle ID in ascending order. The generated table is inserted into the dataDisplay div on the webpage.

The displayDataByTime() function is called when the "Display Data by Time" button is clicked. It retrieves the cattle data from local storage and calculates the time difference between the feed time and the current time for each cattle object. The cattle objects are then sorted based on the time difference in ascending order. An HTML table is generated to display the cattle data, including the time difference. The generated table is inserted into the dataDisplay div on the webpage.

The formatTimeDifference() function is a utility function used by displayDataByTime() to format the time difference in hours and minutes.

Overall, this code provides a basic interface for adding, removing, and displaying cattle data. The cattle data is stored in the browser's local storage, allowing it to persist across page reloads.
