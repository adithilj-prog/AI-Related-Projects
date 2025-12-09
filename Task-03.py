from selenium import webdriver
from selenium.webdriver.common.by import By

# Create Edge options
options = webdriver.EdgeOptions()
options.set_capability('os', 'Windows')
options.set_capability('os_version', '10')
options.set_capability('browser', 'Edge')
options.set_capability('browser_version', 'latest')
options.set_capability('name', 'Task-04 Login Test - Edge')
options.set_capability('build', 'Prodigy-Task04')

# Connect to BrowserStack
driver = webdriver.Remote(
    command_executor='https://adithilj_UpMtwO:FLBSPjVoSSkhZxNssB3H@hub-cloud.browserstack.com/wd/hub',
    options=options
)

# Swag Labs login page
driver.get("https://www.saucedemo.com/")

driver.find_element(By.ID, "user-name").send_keys("standard_user")
driver.find_element(By.ID, "password").send_keys("secret_sauce")
driver.find_element(By.ID, "login-button").click()

# Assertion: check if login succeeded
assert "Products" in driver.page_source

driver.quit()
