function openPopup(text) {
    const popup = document.getElementById('popup');
    const popupOverlay = document.getElementById('popupOverlay');
    const blurElement = document.getElementById('blur');

    // Set popup text
    document.getElementById('popupText').textContent = text;

    // Show popup and overlay
    popup.style.display = 'block';
    popupOverlay.style.display = 'block';

    // Add blur effect
    blurElement.classList.add('blur');
}

function togglePopup() {
    const popup = document.getElementById('popup');
    const popupOverlay = document.getElementById('popupOverlay');
    const blurElement = document.getElementById('blur');

    // Hide popup and overlay
    popup.style.display = 'none';
    popupOverlay.style.display = 'none';

    // Remove blur effect
    blurElement.classList.remove('blur');
}

document.addEventListener("DOMContentLoaded", () => {
    // Start with the loading screen visible
    const loadingScreen = document.getElementById("loading-screen");
    const content = document.getElementById("content");
  
    // Wait until all assets are loaded
    window.onload = () => {
      // Hide the loading screen
      loadingScreen.style.display = "none";
  
      // Show the main content
      content.style.display = "block";
    };
  });

 
