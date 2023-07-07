// 初始化Vulkan库和创建Vulkan实例
//-----------------------------------------------------------------------
// 包含Vulkan头文件
#include <vulkan/vulkan.h>

int main() {
    // 创建Vulkan实例
    VkInstance instance;
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    // 设置实例创建参数...

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    // 检查result是否成功创建实例...

    // 在此处执行其他初始化操作...

    return 0;
}

// 获取物理设备和选择合适的设备
//-----------------------------------------------------------------------
// 获取物理设备列表
uint32_t deviceCount = 0;
vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
std::vector<VkPhysicalDevice> devices(deviceCount);
vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

// 选择合适的物理设备
VkPhysicalDevice selectedDevice = VK_NULL_HANDLE;
for (const auto &device : devices) {
    // 检查设备是否满足要求...

    // 如果满足要求，则选择该设备
    selectedDevice = device;
    break;
}

// 创建逻辑设备和设备队列
//-----------------------------------------------------------------------
// 获取设备队列族
uint32_t queueFamilyCount = 0;
vkGetPhysicalDeviceQueueFamilyProperties(selectedDevice, &queueFamilyCount,
                                         nullptr);
std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
vkGetPhysicalDeviceQueueFamilyProperties(selectedDevice, &queueFamilyCount,
                                         queueFamilies.data());

// 选择支持图形操作的队列族
uint32_t graphicsQueueFamilyIndex = UINT32_MAX;
for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
    if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        graphicsQueueFamilyIndex = i;
        break;
    }
}

// 创建逻辑设备
VkDevice device;
VkDeviceQueueCreateInfo queueCreateInfo = {};
queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
queueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
queueCreateInfo.queueCount = 1;
float queuePriority = 1.0f;
queueCreateInfo.pQueuePriorities = &queuePriority;

VkDeviceCreateInfo deviceCreateInfo = {};
deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
deviceCreateInfo.queueCreateInfoCount = 1;
deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;

VkResult result =
    vkCreateDevice(selectedDevice, &deviceCreateInfo, nullptr, &device);

// 检查result是否成功创建逻辑设备...

// 在此处执行其他操作...

// 创建交换链
//-----------------------------------------------------------------------
// 获取交换链支持信息
VkSurfaceCapabilitiesKHR surfaceCapabilities;
vkGetPhysicalDeviceSurfaceCapabilitiesKHR(selectedDevice, surface,
                                          &surfaceCapabilities);

// 获取交换链支持的表面格式
uint32_t formatCount;
vkGetPhysicalDeviceSurfaceFormatsKHR(selectedDevice, surface, &formatCount,
                                     nullptr);
std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
vkGetPhysicalDeviceSurfaceFormatsKHR(selectedDevice, surface, &formatCount,
                                     surfaceFormats.data());

// 选择交换链表面格式和图像数量
VkSurfaceFormatKHR selectedSurfaceFormat;
for (const auto &surfaceFormat : surfaceFormats) {
    if (surfaceFormat.format == desiredFormat &&
        surfaceFormat.colorSpace == desiredColorSpace) {
        selectedSurfaceFormat = surfaceFormat;
        break;
    }
}

// 创建交换链
VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
swapchainCreateInfo.surface = surface;
swapchainCreateInfo.minImageCount = desiredImageCount;
swapchainCreateInfo.imageFormat = selectedSurfaceFormat.format;
swapchainCreateInfo.imageColorSpace = selectedSurfaceFormat.colorSpace;
swapchainCreateInfo.imageExtent = surfaceCapabilities.currentExtent;
swapchainCreateInfo.imageArrayLayers = 1;
swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
swapchainCreateInfo.presentMode = selectedPresentMode;
swapchainCreateInfo.clipped = VK_TRUE;
swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

VkSwapchainKHR swapchain;
vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain);

// 在此处执行其他操作...

// 创建渲染通道和渲染管线
//-----------------------------------------------------------------------
// 创建渲染通道
VkRenderPassCreateInfo renderPassCreateInfo = {};
// 设置渲染通道参数...
VkRenderPass renderPass;
vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass);

// 创建渲染管线
VkPipelineShaderStageCreateInfo shaderStageCreateInfo = {};
// 设置顶点着色器和片段着色器等参数...
VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
// 设置管线布局参数...
VkPipelineLayout pipelineLayout;
vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr,
                       &pipelineLayout);

VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
// 设置渲染管线参数...
VkPipeline pipeline;
vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineCreateInfo,
                          nullptr, &pipeline);

// 在此处执行其他操作...

// 创建顶点缓冲区和索引缓冲区
//-----------------------------------------------------------------------
//  顶点数据数组
std::vector<Vertex> vertices = {
    // 设置顶点坐标和颜色等数据...
};

// 创建顶点缓冲区
VkBuffer vertexBuffer;
VkDeviceMemory vertexBufferMemory;

VkBufferCreateInfo bufferCreateInfo = {};
// 设置顶点缓冲区参数...
vkCreateBuffer(device, &bufferCreateInfo, nullptr, &vertexBuffer);

VkMemoryRequirements memoryRequirements;
vkGetBufferMemoryRequirements(device, vertexBuffer, &memoryRequirements);

VkMemoryAllocateInfo allocateInfo = {};
// 设置顶点缓冲区内存分配参数...
vkAllocateMemory(device, &allocateInfo, nullptr, &vertexBufferMemory);

vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);

// 在此处执行其他操作...

// 创建帧缓冲区
//-----------------------------------------------------------------------
//  获取交换链图像
uint32_t imageCount;
vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
std::vector<VkImage> swapchainImages(imageCount);
vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

// 创建帧缓冲区
std::vector<VkFramebuffer> framebuffers(imageCount);
for (uint32_t i = 0; i < imageCount; ++i) {
    VkImageView attachments[] = {swapchainImageViews[i]};

    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass;
    framebufferCreateInfo.attachmentCount = 1;
    framebufferCreateInfo.pAttachments = attachments;
    framebufferCreateInfo.width = swapchainExtent.width;
    framebufferCreateInfo.height = swapchainExtent.height;
    framebufferCreateInfo.layers = 1;

    vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr,
                        &framebuffers[i]);
}

// 在此处执行其他操作...

// 绘制三角形
//-----------------------------------------------------------------------
//  在渲染循环中，获取下一个可用的图像和对应的帧缓冲区
uint32_t imageIndex;
vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphore,
                      VK_NULL_HANDLE, &imageIndex);

// 开始命令缓冲区，并进行命令的记录和设置
vkResetCommandBuffer(commandBuffer, 0);
VkCommandBufferBeginInfo beginInfo = {};
beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
vkBeginCommandBuffer(commandBuffer, &beginInfo);

// 设置顶点缓冲区和索引缓冲区
vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, offsets);
vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

// 调用vkCmdDrawIndexed命令来执行绘制操作
vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex,
                 vertexOffset, firstInstance);

// 结束命令缓冲区，并提交到设备队列
vkEndCommandBuffer(commandBuffer);

VkSubmitInfo submitInfo = {};
submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
submitInfo.commandBufferCount = 1;
submitInfo.pCommandBuffers = &commandBuffer;

vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);

// 在此处执行其他操作...

// 销毁
//-----------------------------------------------------------------------
// 在程序结束前销毁 Vulkan 对象

// 销毁帧缓冲区
for (auto framebuffer : framebuffers) {
    vkDestroyFramebuffer(device, framebuffer, nullptr);
}

// 销毁顶点缓冲区和顶点缓冲区内存
vkDestroyBuffer(device, vertexBuffer, nullptr);
vkFreeMemory(device, vertexBufferMemory, nullptr);

// 销毁渲染管线
vkDestroyPipeline(device, pipeline, nullptr);
vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

// 销毁渲染通道
vkDestroyRenderPass(device, renderPass, nullptr);

// 销毁交换链
vkDestroySwapchainKHR(device, swapchain, nullptr);

// 销毁逻辑设备
vkDestroyDevice(device, nullptr);

// 销毁 Vulkan 实例
vkDestroyInstance(instance, nullptr);