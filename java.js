// Wait for everything to load
window.addEventListener('load', function() {
  // Hide spinner and show content
  document.getElementById('spinner').style.display = 'none';
  document.getElementById('content').style.display = 'block';
});

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